#ifndef LIBCIC_CLIENTTEST_H
#define LIBCIC_CLIENTTEST_H

DEV_SIMPLE_EXCEPTION(ChainParamsInvalid);
DEV_SIMPLE_EXCEPTION(ChainParamsNotNoProof);

class ClientTest: public Client
{
public:
    /// Trivial forwarding constructor.
    ClientTest(
        ChainParams const& _params,
        int _networkID,
        CI::cnet::Host* _host,
        std::shared_ptr<GasPricer> _gpForAdoption,
        boost::filesystem::path const& _dbPath = boost::filesystem::path(),
        WithExisting _forceAction = WithExisting::Trust,
        TransactionQueue::Limits const& _l = TransactionQueue::Limits{1024, 1024}
    );
    ~ClientTest();

    void setChainParams(std::string const& _genesis);
    void mineBlocks(unsigned _count);
    void modifyTimestamp(int64_t _timestamp);
    void rewindToBlock(unsigned _number);
    bool addBlock(std::string const& _rlp);
    //FIXME
    //bool completeSync();

protected:
    unsigned m_blocksToMine;
    virtual void onNewBlocks(h256s const& _blocks, h256Hash& io_changed) override;
};

ClientTest& asClientTest(Interface& _c);
ClientTest* asClientTest(Interface* _c);

#endif //LIBCIC_CLIENTTEST_H
