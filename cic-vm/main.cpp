#include <libcolcore/libcolcore.h>
#include <libcolcrypto/libcolcrypto.h>
#include <libcicore/libcicore.h>
#include <libcvm/libcvm.h>
#include <libcic/libcic.h>
#include <libcihashseal/libcihashseal.h>

#include <boost/program_options.hpp>
#include <json_spirit/JsonSpiritHeaders.h>

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::cic;

namespace js = json_spirit;
namespace po = boost::program_options;

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

int64_t maxBlockGasLimit()
{
    static int64_t limit = ChainParams(genesisInfo(Network::MainNetwork)).maxGasLimit.convert_to<int64_t>();
    return limit;
}

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

class RLPStreamer
{
public:
    struct Prefs
    {
        string indent;
        bool hexInts = false;
        bool stringInts = true;
        bool forceString = false;
        bool escapeAll = false;
        bool forceHex = true;
    };

    RLPStreamer(ostream& _out, Prefs _p): m_out(_out), m_prefs(_p)
    {
        if (_p.hexInts)
            _out << std::hex << std::showbase << std::nouppercase;
    }

    void output(RLP const& _d, unsigned _level = 0)
    {
        if (_d.isNull())
            m_out << "null";
        else if (_d.isInt() && !m_prefs.stringInts)
            m_out << _d.toInt<bigint>(RLP::LaissezFaire);
        else if (_d.isData() || (_d.isInt() && m_prefs.stringInts))
            if (m_prefs.forceString || (!m_prefs.forceHex && isAscii(_d.toString())))
                m_out << escaped(_d.toString(), m_prefs.escapeAll);
            else
                m_out << "\"" << toHexPrefixed(_d.toBytes()) << "\"";
        else if (_d.isList())
        {
            m_out << "[";
            string newline = "\n";
            for (unsigned i = 0; i < _level + 1; ++i)
                newline += m_prefs.indent;
            int j = 0;
            for (auto i: _d)
            {
                m_out << (j++ ?
                    (m_prefs.indent.empty() ? ", " : ("," + newline)) :
                    (m_prefs.indent.empty() ? " " : newline));
                output(i, _level + 1);
            }
            newline = newline.substr(0, newline.size() - m_prefs.indent.size());
            m_out << (m_prefs.indent.empty() ? (j ? " ]" : "]") : (j ? newline + "]" : "]"));
        }
    }

private:
    std::ostream& m_out;
    Prefs m_prefs;
};

int main(int argc, char **argv)
{
    string inputFile;
    strings otherInputs;
    Mode mode = Mode::Statistics;
    RLPStreamer::Prefs prefs;
    Encoding encoding = Encoding::Auto;
    bool lenience = true;
    bool quiet = false;
    bool encrypt = false;

    po::options_description transactionOptions("Transaction options", c_lineWidth);
    po::options_description networkOptions("Network options", c_lineWidth);
    po::options_description optionsForTrace("Options for trace", c_lineWidth);
    po::options_description loggingProgramOptions("", c_lineWidth);

    po::options_description generalOptions("General options", c_lineWidth);
    auto addGeneralOption = generalOptions.add_options();
    addGeneralOption("help,h", "Show this help message and exit.");

    po::options_description allowedOptions("Usage ethvm <options> [trace|stats|output|test] (<file>|-)");

    allowedOptions.add(vmProgramOptions(c_lineWidth))
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

    bytes in;
    bytes b;

    State state(0);
    Address sender = Address(69);
    Transaction t;
    bytes data = fromHex(inputFile);
    u256 value = 0;
    u256 gasPrice = 0;
    u256 gas = maxBlockGasLimit();
    Address contractDestination("1122334455667788991011121314151617181920");
    t = Transaction(value, gasPrice, gas, contractDestination, data, 0);
    //state.addBalance(sender, value);

    if (boost::filesystem::is_regular_file(inputFile))
    {
        cout<<"is_regular_file(inputFile)"<<endl;
        in = contents(inputFile);
        cout<<in<<endl;

        if (encoding == Encoding::Auto)
        {
            encoding = Encoding::Hex;
            for (char b: in)
                if (b != '\n' && b != ' ' && b != '\t')
                {
                    if (encoding == Encoding::Hex && (b < '0' || b > '9' ) && (b < 'a' || b > 'f' ) && (b < 'A' || b > 'F' ))
                    {
//                      cerr << "'" << b << "':" << (int)b << endl;
                        encoding = Encoding::Base64;
                    }
                    if (encoding == Encoding::Base64 && (b < '0' || b > '9' ) && (b < 'a' || b > 'z' ) && (b < 'A' || b > 'Z' ) && b != '+' && b != '/')
                    {
                        encoding = Encoding::Binary;
                        break;
                    }
                }
        }
        switch (encoding)
        {
            case Encoding::Hex:
                cout<<"Hex"<<endl;
            break;
            case Encoding::Base64:
                cout<<"Base64"<<endl;
            break;
            case Encoding::Binary:
                cout<<"Binary"<<endl;
            break;
            default:
                cout<<"Unknow"<<endl;
            break;
        }

        /*
        string s = asString(in);
        cout<<s<<endl;
        boost::algorithm::replace_all(s, " ", "");
        boost::algorithm::replace_all(s, "\n", "");
        boost::algorithm::replace_all(s, "\t", "");
        b = asBytes(s);
        cout<<b<<endl;
        RLPStream r;
        r.append(b);
        cout<<toHex(r.out())<<endl;
        */

        RLP rlp(b);
        vector<js::mValue> v(1);
        try {
            js::read_string(asString(in), v[0]);
        }
        catch (...)
        {
            cerr << "Error: Invalid format; bad JSON." << endl;
            exit(1);
        }
        RLPStream out;

        while (!v.empty())
        {
            auto vb = v.back();
            v.pop_back();
            switch (vb.type())
            {
            case js::array_type:
            {
                js::mArray a = vb.get_array();
                out.appendList(a.size());
                for (int i = a.size() - 1; i >= 0; --i)
                    v.push_back(a[i]);
                break;
            }
            case js::str_type:
            {
                string const& s = vb.get_str();
                if (s.size() >= 2 && s.substr(0, 2) == "0x")
                    out << fromHex(s);
                else
                {
                    // assume it's a normal JS escaped string.
                    bytes ss;
                    ss.reserve(s.size());
                    for (unsigned i = 0; i < s.size(); ++i)
                        if (s[i] == '\\' && i + 1 < s.size())
                        {
                            if (s[++i] == 'x' && i + 2 < s.size())
                                ss.push_back(fromHex(s.substr(i, 2))[0]);
                        }
                        else if (s[i] != '\\')
                            ss.push_back((byte)s[i]);
                    out << ss;
                }
                break;
            }
            case js::int_type:
                out << vb.get_int();
                break;
            default:
                cerr << "ERROR: Unsupported type in JSON." << endl;
                if (!lenience)
                    exit(1);
            }
        }
        cout<<toHex(out.out())<<endl;
        putOut(out.out(), encoding, encrypt, quiet);
    }

    return 0;
}
