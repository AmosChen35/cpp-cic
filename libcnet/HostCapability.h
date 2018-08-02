#ifndef LIBCNET_HOSTCAPABILITY_H
#define LIBCNET_HOSTCAPABILITY_H

class HostCapabilityFace
{
    friend class Host;
    template <class T> friend class HostCapability;

    friend class Capability;
    friend class Session;

public:
    HostCapabilityFace() {}
    virtual ~HostCapabilityFace() {}

    Host* host() const { return m_host; }

    //FIXME
    //std::vector<std::pair<std::shared_ptr<SessionFace>, std::shared_ptr<Peer>>> peerSessions() const;
    //std::vector<std::pair<std::shared_ptr<SessionFace>, std::shared_ptr<Peer>>> peerSessions(u256 const& _version) const;

protected:
    virtual std::string name() const = 0;
    virtual u256 version() const = 0;
    CapDesc capDesc() const { return std::make_pair(name(), version()); }
    virtual unsigned messageCount() const = 0;

    //FIXME
    //virtual std::shared_ptr<Capability> newPeerCapability(std::shared_ptr<SessionFace> const& _s, unsigned _idOffset, CapDesc const& _cap) = 0;

    virtual void onStarting() {}
    virtual void onStopping() {}

private:
    Host* m_host = nullptr;
};

template<class PeerCap>
class HostCapability: public HostCapabilityFace
{
public:
    HostCapability() {}
    virtual ~HostCapability() {}

    static std::string staticName() { return PeerCap::name(); }
    static u256 staticVersion() { return PeerCap::version(); }
    static unsigned staticMessageCount() { return PeerCap::messageCount(); }

protected:
    virtual std::string name() const { return PeerCap::name(); }
    virtual u256 version() const { return PeerCap::version(); }
    virtual unsigned messageCount() const { return PeerCap::messageCount(); }

    virtual std::shared_ptr<Capability> newPeerCapability(std::shared_ptr<SessionFace> const& _s, unsigned _idOffset, CapDesc const& _cap)
    {
        auto p = std::make_shared<PeerCap>(_s, this, _idOffset, _cap);
        _s->registerCapability(_cap, p);
        return p;
    }
};

#endif //LIBCNET_HOSTCAPABILITY_H
