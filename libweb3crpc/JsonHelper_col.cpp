#include "libweb3crpc.h"

using namespace std;

namespace CI
{
namespace col
{

Json::Value toJson(unordered_map<u256, u256> const& _storage)
{
    Json::Value res(Json::objectValue);
    for (auto i: _storage)
        res[toJS(i.first)] = toJS(i.second);
    return res;
}

Json::Value toJson(map<h256, pair<u256, u256>> const& _storage)
{
    Json::Value res(Json::objectValue);
    for (auto i: _storage)
        res[toJS(u256(i.second.first))] = toJS(i.second.second);
    return res;
}

Json::Value toJson(Address const& _address)
{
    return toJS(_address);
}

} //namespace col
} //namespace CI
