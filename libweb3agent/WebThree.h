#ifndef LIBWEB3AGENT_WEBTHREE_H
#define LIBWEB3AGENT_WEBTHREE_H

enum WorkState
{
    Active = 0,
    Deleting,
    Deleted
};

class NetworkFace
{
public:
    virtual ~NetworkFace() = default;

    /// Get information concerning this node.

    virtual CI::cnet::NodeInfo nodeInfo() const = 0;

    //FIXME
    /*
    /// Get information on the current peer set.
    virtual std::vector<CI::cnet::PeerSessionInfo> peers() = 0;

    /// Same as peers().size(), but more efficient.
    virtual size_t peerCount() const = 0;

    /// Generalised peer addition.
    virtual void addPeer(CI::cnet::NodeSpec const& _node, CI::cnet::PeerType _t) = 0;

    /// Add node to connect to.
    virtual void addNode(CI::cnet::NodeID const& _node, bi::tcp::endpoint const& _hostEndpoint) = 0;

    /// Require connection to peer.
    virtual void requirePeer(CI::cnet::NodeID const& _node, bi::tcp::endpoint const& _endpoint) = 0;

    /// Save peers
    virtual CI::col::bytes saveNetwork() = 0;

    /// Sets the ideal number of peers.
    virtual void setIdealPeerCount(size_t _n) = 0;
    */

    //FIXME
    //virtual bool haveNetwork() const = 0;

    virtual CI::cnet::NetworkPreferences const& networkPreferences() const = 0;

    //FIXME
    //virtual void setNetworkPreferences(CI::cnet::NetworkPreferences const& _n, bool _dropPeers) = 0;

    //FIXME
    //virtual CI::cnet::NodeID id() const = 0;

    /// Get network id
    virtual u256 networkId() const = 0;

    /// Gets the nodes.
    //FIXME
    //virtual CI::cnet::Peers nodes() const = 0;

    /// Start the network subsystem.
    virtual void startNetwork() = 0;

    /// Stop the network subsystem.
    virtual void stopNetwork() = 0;

    /// Is network working? there may not be any peers yet.
    virtual bool isNetworkStarted() const = 0;

    /// Get enode string.
    virtual std::string enode() const = 0;
};


/**
 * @brief Main API hub for interfacing with Web 3 components. This doesn't do any local multiplexing, so you can only have one
 * running on any given machine for the provided DB path.
 *
 * Keeps a libp2p Host going (administering the work thread with m_workNet).
 *
 * Encapsulates a bunch of P2P protocols (interfaces), each using the same underlying libp2p Host.
 *
 * Provides a baseline for the multiplexed multi-protocol session class, WebThree.
 */
class WebThreeDirect: public NetworkFace
{
public:
    /// Constructor for private instance. If there is already another process on the machine using @a _dbPath, then this will throw an exception.
    /// ethereum() may be safely static_cast()ed to a CI::cic::Client*.
    WebThreeDirect(std::string const& _clientVersion, boost::filesystem::path const& _dbPath,
        boost::filesystem::path const& _snapshotPath, CI::cic::ChainParams const& _params,
        WithExisting _we = WithExisting::Trust,
        std::set<std::string> const& _interfaces = {"eth", "shh", "bzz"},
        CI::cnet::NetworkPreferences const& _n = CI::cnet::NetworkPreferences(),
        bytesConstRef _network = bytesConstRef(), bool _testing = false);

    /// Destructor.
    ~WebThreeDirect() override;

    // The mainline interfaces:

    CI::cic::Client* ethereum() const
    {
        if (!m_ethereum)
            BOOST_THROW_EXCEPTION(InterfaceNotSupported() << errinfo_interface("eth"));
        return m_ethereum.get();
    }

    // Misc stuff:

    static std::string composeClientVersion(std::string const& _client);
    std::string const& clientVersion() const { return m_clientVersion; }

    // Network stuff:

    //FIXME
    /*
    /// Get information on the current peer set.
    std::vector<CI::cnet::PeerSessionInfo> peers() override;

    /// Same as peers().size(), but more efficient.
    size_t peerCount() const override;

    /// Generalised peer addition.
    virtual void addPeer(CI::cnet::NodeSpec const& _node, CI::cnet::PeerType _t) override;

    /// Add node to connect to.
    virtual void addNode(CI::cnet::NodeID const& _node, bi::tcp::endpoint const& _hostEndpoint) override;

    /// Add node to connect to.
    void addNode(CI::cnet::NodeID const& _node, std::string const& _hostString) { addNode(_node, CI::cnet::Network::resolveHost(_hostString)); }

    /// Add node to connect to.
    void addNode(bi::tcp::endpoint const& _endpoint) { addNode(CI::cnet::NodeID(), _endpoint); }

    /// Add node to connect to.
    void addNode(std::string const& _hostString) { addNode(CI::cnet::NodeID(), _hostString); }

    /// Require connection to peer.
    void requirePeer(CI::cnet::NodeID const& _node, bi::tcp::endpoint const& _endpoint) override;

    /// Require connection to peer.
    void requirePeer(CI::cnet::NodeID const& _node, std::string const& _hostString) { requirePeer(_node, CI::cnet::Network::resolveHost(_hostString)); }

    /// Save peers
    CI::col::bytes saveNetwork() override;

    /// Sets the ideal number of peers.
    void setIdealPeerCount(size_t _n) override;

    /// Experimental. Sets ceiling for incoming connections to multiple of ideal peer count.
    void setPeerStretch(size_t _n);
    */

    //FIXME
    //bool haveNetwork() const override { return m_net.haveNetwork(); }

    CI::cnet::NetworkPreferences const& networkPreferences() const override;

    //FIXME
    //void setNetworkPreferences(CI::cnet::NetworkPreferences const& _n, bool _dropPeers = false) override;

    CI::cnet::NodeInfo nodeInfo() const override { return m_net.nodeInfo(); }

    //FIXME
    //CI::cnet::NodeID id() const override { return m_net.id(); }

    u256 networkId() const override { return m_ethereum.get()->networkId(); }

    std::string enode() const override { return m_net.enode(); }

    //FIXME
    /*
    /// Gets the nodes.
    CI::cnet::Peers nodes() const override { return m_net.getPeers(); }
    */

    /// Start the network subsystem.
    void startNetwork() override { m_net.start(); }

    /// Stop the network subsystem.
    void stopNetwork() override { m_net.stop(); }

    /// Is network working? there may not be any peers yet.
    bool isNetworkStarted() const override { return m_net.isStarted(); }

private:
    std::string m_clientVersion;                    ///< Our end-application client's name/version.

    std::unique_ptr<CI::cic::Client> m_ethereum;        ///< Client for Ethereum ("eth") protocol.

    CI::cnet::Host m_net;                                ///< Should run in background and send us events when blocks found and allow us to send blocks as required.
};

#endif //LIBWEB3AGENT_WEBTHREE_H
