#ifndef LIBWEB3CRPC_ETH_H
#define LIBWEB3CRPC_ETH_H

/**
 * @brief JSON-RPC api implementation
 */
class Eth: public CI::crpc::EthFace
{
public:
    Eth(CI::cic::Interface& _eth, CI::cic::AccountHolder& _ethAccounts);

    virtual RPCModules implementedModules() const override
    {
        return RPCModules{RPCModule{"eth", "1.0"}};
    }

    CI::cic::AccountHolder const& ethAccounts() const { return m_ethAccounts; }

    virtual std::string eth_protocolVersion() override;
    //FIXME
    //virtual std::string eth_hashrate() override;
    virtual std::string eth_coinbase() override;
    virtual bool eth_mining() override;
    virtual std::string eth_gasPrice() override;
    virtual Json::Value eth_accounts() override;
    virtual std::string eth_blockNumber()override;
    virtual std::string eth_getBalance(std::string const& _address, std::string const& _blockNumber) override;
    virtual std::string eth_getStorageAt(std::string const& _address, std::string const& _position, std::string const& _blockNumber) override;
    virtual std::string eth_getStorageRoot(std::string const& _address, std::string const& _blockNumber) override;
    virtual std::string eth_getTransactionCount(std::string const& _address, std::string const& _blockNumber) override;
    virtual Json::Value eth_pendingTransactions() override;
    virtual Json::Value eth_getBlockTransactionCountByHash(std::string const& _blockHash) override;
    virtual Json::Value eth_getBlockTransactionCountByNumber(std::string const& _blockNumber) override;
    virtual Json::Value eth_getUncleCountByBlockHash(std::string const& _blockHash) override;
    virtual Json::Value eth_getUncleCountByBlockNumber(std::string const& _blockNumber) override;
    virtual std::string eth_getCode(std::string const& _address, std::string const& _blockNumber) override;
    virtual std::string eth_sendTransaction(Json::Value const& _json) override;
    virtual std::string eth_call(Json::Value const& _json, std::string const& _blockNumber) override;
    virtual std::string eth_estimateGas(Json::Value const& _json) override;
    virtual bool eth_flush() override;

    //FIXME
    /*
    virtual Json::Value eth_getBlockByHash(std::string const& _blockHash, bool _includeTransactions) override;
    */
    virtual Json::Value eth_getBlockByNumber(std::string const& _blockNumber, bool _includeTransactions) override;
    virtual Json::Value eth_getTransactionByHash(std::string const& _transactionHash) override;
    virtual Json::Value eth_getTransactionByBlockHashAndIndex(std::string const& _blockHash, std::string const& _transactionIndex) override;
    virtual Json::Value eth_getTransactionByBlockNumberAndIndex(std::string const& _blockNumber, std::string const& _transactionIndex) override;
    virtual Json::Value eth_getTransactionReceipt(std::string const& _transactionHash) override;
    virtual Json::Value eth_getUncleByBlockHashAndIndex(std::string const& _blockHash, std::string const& _uncleIndex) override;
    virtual Json::Value eth_getUncleByBlockNumberAndIndex(std::string const& _blockNumber, std::string const& _uncleIndex) override;
    virtual std::string eth_newFilter(Json::Value const& _json) override;
    virtual std::string eth_newFilterEx(Json::Value const& _json) override;

    //FIXME
    /*
    virtual std::string eth_newBlockFilter() override;
    virtual std::string eth_newPendingTransactionFilter() override;
    */

    virtual bool eth_uninstallFilter(std::string const& _filterId) override;
    virtual Json::Value eth_getFilterChanges(std::string const& _filterId) override;
    virtual Json::Value eth_getFilterChangesEx(std::string const& _filterId) override;
    virtual Json::Value eth_getFilterLogs(std::string const& _filterId) override;
    virtual Json::Value eth_getFilterLogsEx(std::string const& _filterId) override;
    virtual Json::Value eth_getLogs(Json::Value const& _json) override;
    virtual Json::Value eth_getLogsEx(Json::Value const& _json) override;

    //FIXME
    /*
    virtual Json::Value eth_getWork() override;
    virtual bool eth_submitWork(std::string const& _nonce, std::string const&, std::string const& _mixHash) override;
    virtual bool eth_submitHashrate(std::string const& _hashes, std::string const& _id) override;
    */

    virtual std::string eth_register(std::string const& _address) override;
    virtual bool eth_unregister(std::string const& _accountId) override;
    virtual Json::Value eth_fetchQueuedTransactions(std::string const& _accountId) override;
    virtual std::string eth_signTransaction(Json::Value const& _transaction) override;
    virtual Json::Value eth_inspectTransaction(std::string const& _rlp) override;
    virtual std::string eth_sendRawTransaction(std::string const& _rlp) override;
    virtual bool eth_notePassword(std::string const&) override { return false; }
    virtual Json::Value eth_syncing() override;
    virtual std::string eth_chainId() override;

    void setTransactionDefaults(CI::cic::TransactionSkeleton& _t);
protected:

    CI::cic::Interface* client() { return &m_eth; }

    CI::cic::Interface& m_eth;
    CI::cic::AccountHolder& m_ethAccounts;

};

#endif //LIBWEB3CRPC_ETH_H
