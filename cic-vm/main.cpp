#include <libcolcore/libcolcore.h>
#include <libcolcrypto/libcolcrypto.h>
#include <libcicore/libcicore.h>
#include <libcvm/libcvm.h>
#include <libcic/libcic.h>
#include <libcnet/libcnet.h>
#include <libcihashseal/libcihashseal.h>
#include <libweb3agent/libweb3agent.h>
#include <libweb3crpc/libweb3crpc.h>

#include <boost/program_options.hpp>
#include <json_spirit/JsonSpiritHeaders.h>

#include <cic-buildinfo.h>

#include "MinerAux.h"

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::cic;
using namespace CI::cnet;
using namespace CI::crpc;

namespace po = boost::program_options;
namespace fs = boost::filesystem;

namespace
{

unsigned const c_lineWidth = 160;

enum class Encoding {
    Auto,
    Hex,
    Base64,
    Binary,
    Keccak,
};

enum class Mode
{
    Trace,
    Statistics,
    OutputOnly,

    /// Test mode -- output information needed for test verification and
    /// benchmarking. The execution is not introspected not to degrade
    /// performance.
    Test
};

} //namespace

void putOut(bytes _out, Encoding _encoding, bool _encrypt, bool _quiet)
{
    h256 h = sha3(_out);
    if (_encrypt)
        crypto::Secp256k1PP::get()->encrypt(toPublic(Secret(h)), _out);
    if (!_quiet)
        cerr << "Keccak of RLP: " << h.hex() << endl;

    switch (_encoding)
    {
    case Encoding::Hex: case Encoding::Auto:
        cout << toHex(_out) << endl;
        break;
    case Encoding::Base64:
        //cout << toBase64(&_out) << endl;
        break;
    case Encoding::Binary:
        cout.write((char const*)_out.data(), _out.size());
        cout<<endl;
        break;
    case Encoding::Keccak:
        //cout << sha3(_out).hex() << endl;
        break;
    }
}

bool isAscii(string const& _s)
{
    // Always hex-encode anything beginning with 0x to avoid ambiguity.
    if (_s.size() >= 2 && _s.substr(0, 2) == "0x")
        return false;

    for (char c: _s)
        if (c < 32)
            return false;
    return true;
}

namespace
{

enum class NodeMode
{
    PeerServer,
    Full
};

std::atomic<bool> g_silence = {false};

void version()
{
    const auto* buildinfo = cic_get_buildinfo();
    cout << "aleth " << buildinfo->project_version << "\n";
    cout << "eth network protocol version: " << CI::cic::c_protocolVersion << "\n";
    cout << "Client database version: " << CI::cic::c_databaseVersion << "\n";
    cout << "Build: " << buildinfo->system_name << "/" << buildinfo->build_type << "\n";
}

void stopSealingAfterXBlocks(CI::cic::Client* _c, unsigned _start, unsigned& io_mining)
{
    try
    {
        if (io_mining != ~(unsigned)0 && io_mining && asEthashClient(_c)->isMining() && _c->blockChain().details().number - _start == io_mining)
        {
            _c->stopSealing();
            io_mining = ~(unsigned)0;
        }
    }
    catch (InvalidSealEngine&)
    {
    }

    this_thread::sleep_for(chrono::milliseconds(100));
}

class ExitHandler
{
public:
    static void exitHandler(int) { s_shouldExit = true; }
    bool shouldExit() const { return s_shouldExit; }

private:
    static bool s_shouldExit;
};

bool ExitHandler::s_shouldExit = false;

}

int main(int argc, char **argv)
{
    string inputFile;
    strings otherInputs;
    Mode mode = Mode::Statistics;
    Encoding encoding = Encoding::Auto;
    bool lenience = true;
    bool quiet = false;
    bool encrypt = false;

    bool chainConfigIsSet = false;

    string jsonAdmin;
    ChainParams chainParams;
    fs::path configPath;
    string configJSON;

    bool ipc = true;

    bool upnp = true;
    WithExisting withExisting = WithExisting::Trust;

    /// Wallet password stuff
    string masterPassword;
    bool masterSet = false;

    bool testingMode = false;

    NodeMode nodeMode = NodeMode::Full;

    strings passwordsToNote;

    bytes extraData;

    unsigned mining = 0;

    u256 askPrice = 0;
    u256 bidPrice = DefaultGasPrice;
    bool alwaysConfirm = true;

    /// Networking params.
    string listenIP;
    unsigned short listenPort = 30303;
    string publicIP;
    string remoteHost;
    unsigned short remotePort = 30303;

    static const unsigned NoNetworkID = (unsigned)-1;
    unsigned networkID = NoNetworkID;

    Address author;
    fs::path configFile = getDataDir() / fs::path("config.rlp");
    bytes b = contents(configFile);
    if (b.size())
    {
        try
        {
            RLP config(b);
            author = config[1].toHash<Address>();
        }
        catch (...) {}
    }


    string privateChain;
    bool disableDiscovery = false;
    bool enableDiscovery = false;

    std::string snapshotPath;

    po::options_description transactionOptions("Transaction options", c_lineWidth);
    po::options_description networkOptions("Network options", c_lineWidth);
    po::options_description optionsForTrace("Options for trace", c_lineWidth);
    po::options_description loggingProgramOptions("", c_lineWidth);
    po::options_description clientMining("CLIENT MINING", c_lineWidth);
    auto addMininigOption = clientMining.add_options();
    addMininigOption("address,a", po::value<Address>()->value_name("<addr>"),
        "Set the author (mining payout) address (default: auto)");
    addMininigOption("mining,m", po::value<string>()->value_name("<on/off/number>"),
        "Enable mining; optionally for a specified number of blocks (default: off)");

    po::options_description generalOptions("General options", c_lineWidth);
    auto addGeneralOption = generalOptions.add_options();
    addGeneralOption("version,V", "Show the version and exit");
    addGeneralOption("help,h", "Show this help message and exit.");

    po::options_description allowedOptions("Usage ethvm <options> [trace|stats|output|test] (<file>|-)");

    allowedOptions.add(vmProgramOptions(c_lineWidth))
        .add(clientMining)
        .add(networkOptions)
        .add(optionsForTrace)
        .add(loggingProgramOptions)
        .add(generalOptions)
        .add(transactionOptions);

    po::parsed_options parsed = po::command_line_parser(argc, argv).options(allowedOptions).allow_unregistered().run();
    vector<string> unrecognisedOptions = collect_unrecognized(parsed.options, po::include_positional);
    po::variables_map vm;
    po::store(parsed, vm);
    po::notify(vm);


    for (auto const& arg : unrecognisedOptions)
    {
        if (arg == "stats")
            mode = Mode::Statistics;
        else if (arg == "output")
            mode = Mode::OutputOnly;
        else if (arg == "trace")
            mode = Mode::Trace;
        else if (arg == "test")
            mode = Mode::Test;
        else if (inputFile.empty())
            inputFile = arg;  // Assign input file name only once.
        else
        {
            cerr << "Unknown argument: " << arg << '\n';
            return -1;
        }
    }

    if(vm.count("help"))
    {
        cout << allowedOptions;
        return 0;
    }
    if (vm.count("version"))
    {
        version();
        return 0;
    }
    if (vm.count("mining"))
    {
        string m = vm["mining"].as<string>();
        if (isTrue(m))
            mining = ~(unsigned)0;
        else if (isFalse(m))
            mining = 0;
        else
            try
            {
                mining = stoi(m);
            }
            catch (...) {
                cerr << "Unknown --mining option: " << m << "\n";
                return -1;
            }
    }
    if (vm.count("address"))
    {
        try
        {
            author = vm["address"].as<Address>();
        }
        catch (BadHexCharacter&)
        {
            cerr << "Bad hex in " << "--address" << " option: " << vm["address"].as<string>() << "\n";
            return -1;
        }
        catch (...)
        {
            cerr << "Bad " << "--address" << " option: " << vm["address"].as<string>() << "\n";
            return -1;
        }
    }

    if (!configJSON.empty())
    {
        try
        {
            chainParams = chainParams.loadConfig(configJSON, {}, configPath);
            chainConfigIsSet = true;
        }
        catch (...)
        {
            cerr << "provided configuration is not well formatted\n";
            //cerr << "sample: \n" << genesisInfo(CI::cic::Network::MainNetworkTest) << "\n";
            return 0;
        }
    }

    if (!chainConfigIsSet)
        // default to mainnet if not already set with any of `--mainnet`, `--ropsten`, `--genesis`, `--config`
        chainParams = ChainParams(genesisInfo(CI::cic::Network::MainNetwork), genesisStateRoot(CI::cic::Network::MainNetwork));

    fs::path secretsPath;
    if (testingMode)
        secretsPath = boost::filesystem::path(getDataDir()) / "keystore";
    else
        secretsPath = SecretStore::defaultPath();

    KeyManager keyManager(KeyManager::defaultPath(), secretsPath);
    for (auto const& s: passwordsToNote)
        keyManager.notePassword(s);

    writeFile(configFile, rlpList(author, author));

    string logbuf;
    std::string additional;

    auto getPassword = [&](string const& prompt) {
        bool s = g_silence;
        g_silence = true;
        cout << "\n";
        string ret = CI::col::getPassword(prompt);
        g_silence = s;
        return ret;
    };
    auto getResponse = [&](string const& prompt, unordered_set<string> const& acceptable) {
        bool s = g_silence;
        g_silence = true;
        cout << "\n";
        string ret;
        while (true)
        {
            cout << prompt;
            getline(cin, ret);
            if (acceptable.count(ret))
                break;
            cout << "Invalid response: " << ret << "\n";
        }
        g_silence = s;
        return ret;
    };
    auto getAccountPassword = [&](Address const& a){
        return getPassword("Enter password for address " + keyManager.accountName(a) + " (" + a.abridged() + "; hint:" + keyManager.passwordHint(a) + "): ");
    };

    auto netPrefs = publicIP.empty() ? NetworkPreferences(listenIP, listenPort, upnp) : NetworkPreferences(publicIP, listenIP ,listenPort, upnp);
    netPrefs.discovery = (privateChain.empty() && !disableDiscovery) || enableDiscovery;
    netPrefs.pin = vm.count("pin") != 0;

    auto nodesState = contents(getDataDir() / fs::path("network.rlp"));
    auto caps = set<string>{"eth"};

    if (testingMode)
    {
        chainParams.sealEngineName = "NoProof";
        chainParams.allowFutureBlocks = true;
    }

    CI::col::WebThreeDirect web3(WebThreeDirect::composeClientVersion("cic"), getDataDir(),
        snapshotPath, chainParams, withExisting, nodeMode == NodeMode::Full ? caps : set<string>(),
        netPrefs, &nodesState, testingMode);

    if (!extraData.empty())
        web3.ethereum()->setExtraData(extraData);

    auto toNumber = [&](string const& s) -> unsigned {
        if (s == "latest")
            return web3.ethereum()->number();
        if (s.size() == 64 || (s.size() == 66 && s.substr(0, 2) == "0x"))
            return web3.ethereum()->blockChain().number(h256(s));
        try
        {
            return stol(s);
        }
        catch (...)
        {
            cerr << "Bad block number/hash option: " << s << "\n";
            return -1;
        }
    };

    try
    {
        if (keyManager.exists())
        {
            if (!keyManager.load(masterPassword) && masterSet)
            {
                while (true)
                {
                    masterPassword = getPassword("Please enter your MASTER password: ");
                    if (keyManager.load(masterPassword))
                        break;
                    cout << "The password you entered is incorrect. If you have forgotten your password, and you wish to start afresh, manually remove the file: " << (getDataDir("ethereum") / fs::path("keys.info")).string() << "\n";
                }
            }
        }
        else
        {
            if (masterSet)
                keyManager.create(masterPassword);
            else
                keyManager.create(std::string());
        }
    }
    catch(...)
    {
        cerr << "Error initializing key manager: " << boost::current_exception_diagnostic_information() << "\n";
        return -1;
    }

    std::shared_ptr<CI::cic::TrivialGasPricer> gasPricer = make_shared<CI::cic::TrivialGasPricer>(askPrice, bidPrice);
    CI::cic::Client* c = nodeMode == NodeMode::Full ? web3.ethereum() : nullptr;

    if (c)
    {
        c->setGasPricer(gasPricer);
        c->setSealer("cpu");
        c->setAuthor(author);
        if (networkID != NoNetworkID)
            c->setNetworkId(networkID);
    }

    auto renderFullAddress = [&](Address const& _a) -> std::string
    {
        return toUUID(keyManager.uuid(_a)) + " - " + _a.hex();
    };

    if (author)
        cout << "Mining Beneficiary: " << renderFullAddress(author) << "\n";

    unique_ptr<ModularServer<>> jsonrpcIpcServer;
    unique_ptr<CI::crpc::SessionManager> sessionManager;
    unique_ptr<SimpleAccountHolder> accountHolder;

    AddressHash allowedDestinations;

    std::function<bool(TransactionSkeleton const&, bool)> authenticator;
    if (testingMode)
        authenticator = [](TransactionSkeleton const&, bool) -> bool { return true; };
    else
        authenticator = [&](TransactionSkeleton const& _t, bool isProxy) -> bool {
            // "unlockAccount" functionality is done in the AccountHolder.
            if (!alwaysConfirm || allowedDestinations.count(_t.to))
                return true;

            string r = getResponse(_t.userReadable(isProxy,
                [&](TransactionSkeleton const& _t) -> pair<bool, string>
                {
                    h256 contractCodeHash = web3.ethereum()->postState().codeHash(_t.to);
                    if (contractCodeHash == EmptySHA3)
                        return std::make_pair(false, std::string());
                    // TODO: actually figure out the natspec. we'll need the natspec database here though.
                    return std::make_pair(true, std::string());
                }, [&](Address const& _a) { return _a.hex(); }
            ) + "\nEnter yes/no/always (always to this address): ", {"yes", "n", "N", "no", "NO", "always"});
            if (r == "always")
                allowedDestinations.insert(_t.to);
            return r == "yes" || r == "always";
        };

    ExitHandler exitHandler;

    if (ipc)
    {
        using FullServer = ModularServer<
            CI::crpc::EthFace,
            CI::crpc::NetFace, CI::crpc::Web3Face, CI::crpc::PersonalFace,
            CI::crpc::AdminEthFace, CI::crpc::AdminNetFace,
            CI::crpc::DebugFace, CI::crpc::TestFace
        >;

        sessionManager.reset(new CI::crpc::SessionManager());
        accountHolder.reset(new SimpleAccountHolder([&](){ return web3.ethereum(); }, getAccountPassword, keyManager, authenticator));
        auto ethFace = new CI::crpc::Eth(*web3.ethereum(), *accountHolder.get());
        CI::crpc::TestFace* testEth = nullptr;
        if (testingMode)
            testEth = new CI::crpc::Test(*web3.ethereum());

        jsonrpcIpcServer.reset(new FullServer(
            ethFace, new CI::crpc::Net(web3),
            new CI::crpc::Web3(web3.clientVersion()), new CI::crpc::Personal(keyManager, *accountHolder, *web3.ethereum()),
            new CI::crpc::AdminEth(*web3.ethereum(), *gasPricer.get(), keyManager, *sessionManager.get()),
            new CI::crpc::AdminNet(web3, *sessionManager.get()),
            new CI::crpc::Debug(*web3.ethereum()),
            testEth
        ));
        auto ipcConnector = new IpcServer("geth");
        jsonrpcIpcServer->addConnector(ipcConnector);
        ipcConnector->StartListening();

        if (jsonAdmin.empty())
            jsonAdmin = sessionManager->newSession(CI::crpc::SessionPermissions{{CI::crpc::Privilege::Admin}});
        else
            sessionManager->addSession(jsonAdmin, CI::crpc::SessionPermissions{{CI::crpc::Privilege::Admin}});

        cout << "JSONRPC Admin Session Key: " << jsonAdmin << "\n";
    }

    signal(SIGABRT, &ExitHandler::exitHandler);
    signal(SIGTERM, &ExitHandler::exitHandler);
    signal(SIGINT, &ExitHandler::exitHandler);

    if (c)
    {
        unsigned n = c->blockChain().details().number;
        if (mining)
            c->startSealing();

        while (!exitHandler.shouldExit())
            stopSealingAfterXBlocks(c, n, mining);
    }
    else
        while (!exitHandler.shouldExit())
            this_thread::sleep_for(chrono::milliseconds(1000));

    if (jsonrpcIpcServer.get())
        jsonrpcIpcServer->StopListening();

    return 0;
}
