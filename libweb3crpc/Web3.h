#ifndef LIBWEB3CRPC_WEB3_H
#define LIBWEB3CRPC_WEB3_H

class Web3: public Web3Face
{
public:
    Web3(std::string _clientVersion = "C++ (cpp-ethereum)"): m_clientVersion(std::move(_clientVersion)) {}
    virtual RPCModules implementedModules() const override
    {
        return RPCModules{RPCModule{"web3", "1.0"}};
    }
    virtual std::string web3_sha3(std::string const& _param1) override;
    virtual std::string web3_clientVersion() override { return m_clientVersion; }

private:
    std::string m_clientVersion;
};

#endif //LIBWEB3CRPC_WEB3_H
