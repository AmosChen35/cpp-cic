#ifndef LIBWEB3CRPC_PERSONAL_H
#define LIBWEB3CRPC_PERSONAL_H

class Personal: public CI::crpc::PersonalFace
{
public:
    Personal(CI::cic::KeyManager& _keyManager, CI::cic::AccountHolder& _accountHolder, CI::cic::Interface& _eth);
    virtual RPCModules implementedModules() const override
    {
        return RPCModules{RPCModule{"personal", "1.0"}};
    }
    virtual std::string personal_newAccount(std::string const& _password) override;
    virtual bool personal_unlockAccount(std::string const& _address, std::string const& _password, int _duration) override;
    virtual std::string personal_signAndSendTransaction(Json::Value const& _transaction, std::string const& _password) override;
    virtual std::string personal_sendTransaction(Json::Value const& _transaction, std::string const& _password) override;
    virtual Json::Value personal_listAccounts() override;

private:
    CI::cic::KeyManager& m_keyManager;
    CI::cic::AccountHolder& m_accountHolder;
    CI::cic::Interface& m_eth;
};

#endif //LIBWEB3CRPC_PERSONAL_H

