#ifndef LIBWEB3CRPC_JSONHELPER_COL_H
#define LIBWEB3CRPC_JSONHELPER_COL_H

Json::Value toJson(std::map<h256, std::pair<u256, u256>> const& _storage);
Json::Value toJson(std::unordered_map<u256, u256> const& _storage);
Json::Value toJson(Address const& _address);

template <class T>
Json::Value toJson(std::vector<T> const& _es)
{
    Json::Value res(Json::arrayValue);
    for (auto const& e: _es)
        res.append(toJson(e));
    return res;
}

template <class T>
Json::Value toJson(std::unordered_set<T> const& _es)
{
    Json::Value res(Json::arrayValue);
    for (auto const& e: _es)
        res.append(toJson(e));
    return res;
}

template <class T>
Json::Value toJson(std::set<T> const& _es)
{
    Json::Value res(Json::arrayValue);
    for (auto const& e: _es)
        res.append(toJson(e));
    return res;
}

#endif //LIBWEB3CRPC_JSONHELPER_COL_H
