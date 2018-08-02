#include "libweb3crpc.h"

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::cic;

StandardTrace::DebugOptions CI::cic::debugOptions(Json::Value const& _json)
{
    StandardTrace::DebugOptions op;
    if (!_json.isObject() || _json.empty())
        return op;
    if (!_json["disableStorage"].empty())
        op.disableStorage = _json["disableStorage"].asBool();
    if (!_json["disableMemory"].empty())
        op.disableMemory = _json["disableMemory"].asBool();
    if (!_json["disableStack"].empty())
        op.disableStack =_json["disableStack"].asBool();
    if (!_json["fullStorage"].empty())
        op.fullStorage = _json["fullStorage"].asBool();
    return op;
}
