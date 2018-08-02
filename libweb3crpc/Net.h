#ifndef LIBWEB3CRPC_NET_H
#define LIBWEB3CRPC_NET_H

class Net: public NetFace
{
public:
    Net(NetworkFace& _network);
    virtual RPCModules implementedModules() const override
    {
        return RPCModules{RPCModule{"net", "1.0"}};
    }
    virtual std::string net_version() override;
    //FIXME
    /*
    virtual std::string net_peerCount() override;
    virtual bool net_listening() override;
    */

private:
    NetworkFace& m_network;
};

#endif //LIBWEB3CRPC_NET_H
