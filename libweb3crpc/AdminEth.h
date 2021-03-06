#ifndef LIBWEB3CRPC_ADMINETH_H
#define LIBWEB3CRPC_ADMINETH_H

class AdminEth: public AdminEthFace
{
public:
    AdminEth(CI::cic::Client& _eth, CI::cic::TrivialGasPricer& _gp, CI::cic::KeyManager& _keyManager, SessionManager& _sm);

    virtual RPCModules implementedModules() const override
    {
        return RPCModules{RPCModule{"admin", "1.0"}, RPCModule{"miner", "1.0"}};
    }

    virtual bool admin_eth_setMining(bool _on, std::string const& _session) override;
    virtual Json::Value admin_eth_blockQueueStatus(std::string const& _session) override;
    virtual bool admin_eth_setAskPrice(std::string const& _wei, std::string const& _session) override;
    virtual bool admin_eth_setBidPrice(std::string const& _wei, std::string const& _session) override;
    virtual Json::Value admin_eth_findBlock(std::string const& _blockHash, std::string const& _session) override;
    virtual std::string admin_eth_blockQueueFirstUnknown(std::string const& _session) override;
    virtual bool admin_eth_blockQueueRetryUnknown(std::string const& _session) override;
    virtual Json::Value admin_eth_allAccounts(std::string const& _session) override;
    virtual Json::Value admin_eth_newAccount(const Json::Value& _info, std::string const& _session) override;
    virtual bool admin_eth_setMiningBenefactor(std::string const& _uuidOrAddress, std::string const& _session) override;
    virtual Json::Value admin_eth_inspect(std::string const& _address, std::string const& _session) override;
    virtual Json::Value admin_eth_reprocess(std::string const& _blockNumberOrHash, std::string const& _session) override;
    virtual Json::Value admin_eth_vmTrace(std::string const& _blockNumberOrHash, int _txIndex, std::string const& _session) override;
    virtual Json::Value admin_eth_getReceiptByHashAndIndex(std::string const& _blockNumberOrHash, int _txIndex, std::string const& _session) override;
    virtual bool miner_start(int _threads) override;
    virtual bool miner_stop() override;
    virtual bool miner_setEtherbase(std::string const& _uuidOrAddress) override;
    virtual bool miner_setExtra(std::string const& _extraData) override;
    virtual bool miner_setGasPrice(std::string const& _gasPrice) override;
    //FIXME
    //virtual std::string miner_hashrate() override;

    virtual void setMiningBenefactorChanger(std::function<void(Address const&)> const& _f) { m_setMiningBenefactor = _f; }
private:
    CI::cic::Client& m_eth;
    CI::cic::TrivialGasPricer& m_gp;
    CI::cic::KeyManager& m_keyManager;
    SessionManager& m_sm;
    std::function<void(Address const&)> m_setMiningBenefactor;

    h256 blockHash(std::string const& _blockNumberOrHash) const;
};

#endif //LIBWEB3CRPC_ADMINETH_H
