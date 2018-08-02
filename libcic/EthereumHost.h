#ifndef LIBCIC_ETHEREUMHOST_H
#define LIBCIC_ETHEREUMHOST_H

class EthereumHost: public CI::cnet::HostCapability<EthereumPeer>, Worker
{
public:
    /// Start server, but don't listen.
    EthereumHost(BlockChain const& _ch, OverlayDB const& _db, TransactionQueue& _tq, BlockQueue& _bq, u256 _networkId);

    /// Will block on network process events.
    virtual ~EthereumHost();

    unsigned protocolVersion() const { return c_protocolVersion; }
    u256 networkId() const { return m_networkId; }
    void setNetworkId(u256 _n) { m_networkId = _n; }

    //FIXME
    /*
    void reset();
    /// Don't sync further - used only in test mode
    void completeSync();
    bool isSyncing() const;
    */

    bool isBanned(CI::cnet::NodeID const& _id) const { return !!m_banned.count(_id); }

    void noteNewTransactions() { m_newTransactions = true; }
    void noteNewBlocks() { m_newBlocks = true; }

    //FIXME
    //void onBlockImported(BlockHeader const& _info) { m_sync->onBlockImported(_info); }

    BlockChain const& chain() const { return m_chain; }
    OverlayDB const& db() const { return m_db; }
    BlockQueue& bq() { return m_bq; }
    BlockQueue const& bq() const { return m_bq; }
    //FIXME
    //SyncStatus status() const;
    h256 latestBlockSent() { return m_latestBlockSent; }
    static char const* stateName(SyncState _s) { return s_stateNames[static_cast<int>(_s)]; }

    static unsigned const c_oldProtocolVersion;

    //FIXME
    //void foreachPeer(std::function<bool(std::shared_ptr<EthereumPeer>)> const& _f) const;

protected:
    //FIXME
    //std::shared_ptr<p2p::Capability> newPeerCapability(std::shared_ptr<p2p::SessionFace> const& _s, unsigned _idOffset, p2p::CapDesc const& _cap) override;

private:
    static char const* const s_stateNames[static_cast<int>(SyncState::Size)];

    //FIXME
    //std::tuple<std::vector<std::shared_ptr<EthereumPeer>>, std::vector<std::shared_ptr<EthereumPeer>>, std::vector<std::shared_ptr<p2p::SessionFace>>> randomSelection(unsigned _percent = 25, std::function<bool(EthereumPeer*)> const& _allow = [](EthereumPeer const*){ return true; });

    /// Sync with the BlockChain. It might contain one of our mined blocks, we might have new candidates from the network.
    //FIXME
    /*
    virtual void doWork() override;

    void maintainTransactions();
    void maintainBlocks(h256 const& _currentBlock);
    void onTransactionImported(ImportResult _ir, h256 const& _h, h512 const& _nodeId);
    */

    /// Check to see if the network peer-state initialisation has happened.
    bool isInitialised() const { return (bool)m_latestBlockSent; }

    /// Initialises the network peer-state, doing the stuff that needs to be once-only. @returns true if it really was first.
    bool ensureInitialised();

    //FIXME
    /*
    virtual void onStarting() override { startWorking(); }
    virtual void onStopping() override { stopWorking(); }
    */

    BlockChain const& m_chain;
    OverlayDB const& m_db;                  ///< References to DB, needed for some of the Ethereum Protocol responses.
    TransactionQueue& m_tq;                 ///< Maintains a list of incoming transactions not yet in a block on the blockchain.
    BlockQueue& m_bq;                       ///< Maintains a list of incoming blocks not yet on the blockchain (to be imported).

    u256 m_networkId;

    h256 m_latestBlockSent;
    h256Hash m_transactionsSent;

    std::unordered_set<CI::cnet::NodeID> m_banned;

    bool m_newTransactions = false;
    bool m_newBlocks = false;

    mutable Mutex x_transactions;
    //FIXME
    //std::shared_ptr<BlockChainSync> m_sync;
    std::atomic<time_t> m_lastTick = { 0 };

    std::shared_ptr<EthereumHostDataFace> m_hostData;

    //FIXME
    //std::shared_ptr<EthereumPeerObserverFace> m_peerObserver;

    Logger m_logger{createLogger(VerbosityDebug, "host")};
};

#endif //LIBCIC_ETHEREUMHOST_H
