#include "libcnet.h"

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::cnet;

//FIXME
/*
std::vector<std::pair<std::shared_ptr<SessionFace>, std::shared_ptr<Peer>>> HostCapabilityFace::peerSessions() const
{
    return peerSessions(version());
}

std::vector<std::pair<std::shared_ptr<SessionFace>, std::shared_ptr<Peer>>> HostCapabilityFace::peerSessions(u256 const& _version) const
{
    RecursiveGuard l(m_host->x_sessions);
    std::vector<std::pair<std::shared_ptr<SessionFace>, std::shared_ptr<Peer>>> ret;
    for (auto const& i: m_host->m_sessions)
        if (std::shared_ptr<SessionFace> s = i.second.lock())
            if (s->capabilities().count(std::make_pair(name(), _version)))
                ret.push_back(make_pair(s,s->peer()));
    return ret;
}
*/
