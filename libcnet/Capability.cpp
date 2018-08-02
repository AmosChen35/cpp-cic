#include "libcnet.h"

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::cnet;

Capability::Capability(std::shared_ptr<SessionFace> _s, HostCapabilityFace* _h, unsigned _idOffset):
    m_session(_s), m_hostCap(_h), m_idOffset(_idOffset)
{
    cnetdetails << "New session for capability " << m_hostCap->name()
                << "; idOffset: " << m_idOffset;
}

void Capability::disable(std::string const& _problem)
{
    cnetdetails << "DISABLE: Disabling capability '" << m_hostCap->name()
                << "'. Reason: " << _problem;
    m_enabled = false;
}

RLPStream& Capability::prep(RLPStream& _s, unsigned _id, unsigned _args)
{
    return _s.appendRaw(bytes(1, _id + m_idOffset)).appendList(_args);
}

void Capability::sealAndSend(RLPStream& _s)
{
    shared_ptr<SessionFace> session = m_session.lock();
    if (session)
        session->sealAndSend(_s);
}

void Capability::addRating(int _r)
{
    shared_ptr<SessionFace> session = m_session.lock();
    if (session)
        session->addRating(_r);
}
