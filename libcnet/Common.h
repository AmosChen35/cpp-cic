#ifndef LIBCNET_COMMON_H
#define LIBCNET_COMMON_H

/// Peer network protocol version.
extern const unsigned c_protocolVersion;
extern const unsigned c_defaultIPPort;

class NodeIPEndpoint;
class Node;
extern const NodeIPEndpoint UnspecifiedNodeIPEndpoint;
extern const Node UnspecifiedNode;

using NodeID = h512;

bool isPrivateAddress(bi::address const& _addressToCheck);
bool isPrivateAddress(std::string const& _addressToCheck);
bool isLocalHostAddress(bi::address const& _addressToCheck);
bool isLocalHostAddress(std::string const& _addressToCheck);
bool isPublicAddress(bi::address const& _addressToCheck);
bool isPublicAddress(std::string const& _addressToCheck);

class UPnP;
class Capability;
class Host;
class Session;

struct NetworkStartRequired: virtual CI::col::Exception {};
struct InvalidPublicIPAddress: virtual CI::col::Exception {};

/// The ECDHE agreement failed during RLPx handshake.
struct ECDHEError: virtual Exception {};

#define NET_GLOBAL_LOGGER(NAME, SEVERITY)                      \
    BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(g_##NAME##Logger, \
        boost::log::sources::severity_channel_logger_mt<>,     \
        (boost::log::keywords::severity = SEVERITY)(boost::log::keywords::channel = "net"))

NET_GLOBAL_LOGGER(netnote, VerbosityInfo)
#define cnetnote LOG(CI::cnet::g_netnoteLogger::get())
NET_GLOBAL_LOGGER(netlog, VerbosityDebug)
#define cnetlog LOG(CI::cnet::g_netlogLogger::get())
NET_GLOBAL_LOGGER(netdetails, VerbosityTrace)
#define cnetdetails LOG(CI::cnet::g_netdetailsLogger::get())

enum PacketType
{
    HelloPacket = 0,
    DisconnectPacket,
    PingPacket,
    PongPacket,
    GetPeersPacket,
    PeersPacket,
    UserPacket = 0x10
};

enum DisconnectReason
{
    DisconnectRequested = 0,
    TCPError,
    BadProtocol,
    UselessPeer,
    TooManyPeers,
    DuplicatePeer,
    IncompatibleProtocol,
    NullIdentity,
    ClientQuit,
    UnexpectedIdentity,
    LocalIdentity,
    PingTimeout,
    UserReason = 0x10,
    NoDisconnect = 0xffff
};

inline bool isPermanentProblem(DisconnectReason _r)
{
    switch (_r)
    {
    case DuplicatePeer:
    case IncompatibleProtocol:
    case NullIdentity:
    case UnexpectedIdentity:
    case LocalIdentity:
        return true;
    default:
        return false;
    }
}

/// @returns the string form of the given disconnection reason.
std::string reasonOf(DisconnectReason _r);

using CapDesc = std::pair<std::string, u256>;
using CapDescSet = std::set<CapDesc>;
using CapDescs = std::vector<CapDesc>;

/*
 * Used by Host to pass negotiated information about a connection to a
 * new Peer Session; PeerSessionInfo is then maintained by Session and can
 * be queried for point-in-time status information via Host.
 */
struct PeerSessionInfo
{
    NodeID const id;
    std::string const clientVersion;
    std::string const host;
    unsigned short const port;
    std::chrono::steady_clock::duration lastPing;
    std::set<CapDesc> const caps;
    unsigned socketId;
    std::map<std::string, std::string> notes;
    unsigned const protocolVersion;
};

using PeerSessionInfos = std::vector<PeerSessionInfo>;

enum class PeerType
{
    Optional,
    Required
};

/**
 * @brief IPv4,UDP/TCP endpoints.
 */
class NodeIPEndpoint
{
public:
    enum RLPAppend
    {
        StreamList,
        StreamInline
    };

    /// Setting true causes isAllowed to return true for all addresses. (Used by test fixtures)
    static bool test_allowLocal;

    NodeIPEndpoint() = default;
    NodeIPEndpoint(bi::address _addr, uint16_t _udp, uint16_t _tcp): address(_addr), udpPort(_udp), tcpPort(_tcp) {}
    NodeIPEndpoint(RLP const& _r) { interpretRLP(_r); }

    operator bi::udp::endpoint() const { return bi::udp::endpoint(address, udpPort); }
    operator bi::tcp::endpoint() const { return bi::tcp::endpoint(address, tcpPort); }

    operator bool() const { return !address.is_unspecified() && udpPort > 0 && tcpPort > 0; }

    bool isAllowed() const { return NodeIPEndpoint::test_allowLocal ? !address.is_unspecified() : isPublicAddress(address); }

    bool operator==(NodeIPEndpoint const& _cmp) const {
        return address == _cmp.address && udpPort == _cmp.udpPort && tcpPort == _cmp.tcpPort;
    }
    bool operator!=(NodeIPEndpoint const& _cmp) const {
        return !operator==(_cmp);
    }

    void streamRLP(RLPStream& _s, RLPAppend _append = StreamList) const;
    void interpretRLP(RLP const& _r);

    // TODO: make private, give accessors and rename m_...
    bi::address address;
    uint16_t udpPort = 0;
    uint16_t tcpPort = 0;
};

struct NodeSpec
{
    NodeSpec() {}

    /// Accepts user-readable strings of the form (enode://pubkey@)host({:port,:tcpport.udpport})
    NodeSpec(std::string const& _user);

    NodeSpec(std::string const& _addr, uint16_t _port, int _udpPort = -1):
        m_address(_addr),
        m_tcpPort(_port),
        m_udpPort(_udpPort == -1 ? _port : (uint16_t)_udpPort)
    {}

    NodeID id() const { return m_id; }

    NodeIPEndpoint nodeIPEndpoint() const;

    std::string enode() const;

private:
    std::string m_address;
    uint16_t m_tcpPort = 0;
    uint16_t m_udpPort = 0;
    NodeID m_id;
};

class Node
{
public:
    Node() = default;
    virtual ~Node() = default;
    Node(Node const&);
    Node(Public _publicKey, NodeIPEndpoint const& _ip, PeerType _peerType = PeerType::Optional): id(_publicKey), endpoint(_ip), peerType(_peerType) {}
    Node(NodeSpec const& _s, PeerType _peerType = PeerType::Optional);

    virtual NodeID const& address() const { return id; }
    virtual Public const& publicKey() const { return id; }

    virtual operator bool() const { return (bool)id; }

    // TODO: make private, give accessors and rename m_...
    NodeID id;

    /// Endpoints by which we expect to reach node.
    // TODO: make private, give accessors and rename m_...
    NodeIPEndpoint endpoint;

    // TODO: p2p implement
    std::atomic<PeerType> peerType{PeerType::Optional};
};

class DeadlineOps
{
    class DeadlineOp
    {
    public:
        DeadlineOp(ba::io_service& _io, unsigned _msInFuture, std::function<void(boost::system::error_code const&)> const& _f): m_timer(new ba::deadline_timer(_io)) { m_timer->expires_from_now(boost::posix_time::milliseconds(_msInFuture)); m_timer->async_wait(_f); }
        ~DeadlineOp() { if (m_timer) m_timer->cancel(); }

        DeadlineOp(DeadlineOp&& _s): m_timer(_s.m_timer.release()) {}
        DeadlineOp& operator=(DeadlineOp&& _s)
        {
            assert(&_s != this);

            m_timer.reset(_s.m_timer.release());
            return *this;
        }

        bool expired() { Guard l(x_timer); return m_timer->expires_from_now().total_nanoseconds() <= 0; }
        void wait() { Guard l(x_timer); m_timer->wait(); }

    private:
        std::unique_ptr<ba::deadline_timer> m_timer;
        Mutex x_timer;
    };

public:
    DeadlineOps(ba::io_service& _io, unsigned _reapIntervalMs = 100): m_io(_io), m_reapIntervalMs(_reapIntervalMs), m_stopped(false) { reap(); }
    ~DeadlineOps() { stop(); }

    void schedule(unsigned _msInFuture, std::function<void(boost::system::error_code const&)> const& _f) { if (m_stopped) return; DEV_GUARDED(x_timers) m_timers.emplace_back(m_io, _msInFuture, _f); } 

    void stop() { m_stopped = true; DEV_GUARDED(x_timers) m_timers.clear(); }

    bool isStopped() const { return m_stopped; }

protected:
    void reap();

private:
    ba::io_service& m_io;
    unsigned m_reapIntervalMs;

    std::vector<DeadlineOp> m_timers;
    Mutex x_timers;

    std::atomic<bool> m_stopped;
};

/// Simple stream output for a NodeIPEndpoint.
std::ostream& operator<<(std::ostream& _out, CI::cnet::NodeIPEndpoint const& _ep);

#endif //LIBCNET_COMMON_H