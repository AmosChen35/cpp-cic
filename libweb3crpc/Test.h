#ifndef LIBWEB3CRPC_TEST_H
#define LIBWEB3CRPC_TEST_H

class Test: public TestFace
{
public:
    Test(CI::cic::Client& _eth);
    virtual RPCModules implementedModules() const override
    {
        return RPCModules{RPCModule{"test", "1.0"}};
    }
    virtual std::string test_getLogHash(std::string const& _param1) override;
    virtual bool test_setChainParams(const Json::Value& _param1) override;
    virtual bool test_mineBlocks(int _number) override;
    virtual bool test_modifyTimestamp(int _timestamp) override;
    virtual bool test_addBlock(std::string const& _rlp) override;
    virtual bool test_rewindToBlock(int _number) override;

private:
    CI::cic::Client& m_eth;
};

#endif //LIBWEB3CRPC_TEST_H
