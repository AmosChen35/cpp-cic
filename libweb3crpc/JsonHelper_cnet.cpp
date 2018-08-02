#include "libweb3crpc.h"

using namespace std;

namespace CI
{
namespace cnet
{

Json::Value toJson(CI::cnet::PeerSessionInfo const& _p)
{
    //@todo localAddress
    //@todo protocols
    Json::Value ret;
    ret["id"] = _p.id.hex();
    ret["name"] = _p.clientVersion;
    ret["network"]["remoteAddress"] = _p.host + ":" + toString(_p.port);
    ret["lastPing"] = (int)chrono::duration_cast<chrono::milliseconds>(_p.lastPing).count();
    for (auto const& i: _p.notes)
        ret["notes"][i.first] = i.second;
    for (auto const& i: _p.caps)
        ret["caps"].append(i.first + "/" + toString((unsigned)i.second));
    return ret;
}

} //namespace cnet
} //namespace CI
