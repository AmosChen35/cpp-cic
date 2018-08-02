#ifndef LIBWEB3CRPC_ADMINNET_H
#define LIBWEB3CRPC_ADMINNET_H

class AdminNet: public CI::crpc::AdminNetFace
{
public:
    AdminNet(NetworkFace& _network, SessionManager& _sm);
    virtual RPCModules implementedModules() const override
    {
        return RPCModules{RPCModule{"admin", "1.0"}};
    }
    virtual bool admin_net_start(std::string const& _session) override;
    virtual bool admin_net_stop(std::string const& _session) override;
    //FIXME
    /*
    virtual bool admin_net_connect(std::string const& _node, std::string const& _session) override;
    virtual Json::Value admin_net_peers(std::string const& _session) override;
    */
    virtual Json::Value admin_net_nodeInfo(std::string const& _session) override;
    virtual Json::Value admin_nodeInfo() override;

    //FIXME
    /*
    virtual Json::Value admin_peers() override;
    virtual bool admin_addPeer(std::string const& _node) override;
    */

private:
    NetworkFace& m_network;
    SessionManager& m_sm;
};

#endif //LIBWEB3CRPC_ADMINNET_H
