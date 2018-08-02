#include "libweb3crpc.h"

using namespace CI;
using namespace CI::col;
using namespace CI::cic;
using namespace CI::crpc;

Net::Net(NetworkFace& _network): m_network(_network) {}

std::string Net::net_version()
{
    return toString(m_network.networkId());
}

//FIXME
/*
std::string Net::net_peerCount()
{
    return toJS(m_network.peerCount());
}

bool Net::net_listening()
{
    return m_network.isNetworkStarted();
}
*/
