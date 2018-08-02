#ifndef LIBWEB3CRPC_JSONHELPER_CIC_H
#define LIBWEB3CRPC_JSONHELPER_CIC_H

using Transactions = std::vector<Transaction>;
using UncleHashes = h256s;
using TransactionHashes = h256s;

Json::Value toJson(BlockHeader const& _bi, SealEngineFace* _face = nullptr);
//TODO: wrap these params into one structure eg. "LocalisedTransaction"
Json::Value toJson(Transaction const& _t, std::pair<h256, unsigned> _location, BlockNumber _blockNumber);
Json::Value toJson(BlockHeader const& _bi, BlockDetails const& _bd, UncleHashes const& _us, Transactions const& _ts, SealEngineFace* _face = nullptr);
Json::Value toJson(BlockHeader const& _bi, BlockDetails const& _bd, UncleHashes const& _us, TransactionHashes const& _ts, SealEngineFace* _face = nullptr);
Json::Value toJson(TransactionSkeleton const& _t);
Json::Value toJson(Transaction const& _t);
Json::Value toJson(LocalisedTransaction const& _t);
Json::Value toJson(TransactionReceipt const& _t);
Json::Value toJson(LocalisedTransactionReceipt const& _t);
Json::Value toJson(LocalisedLogEntry const& _e);
Json::Value toJson(LogEntry const& _e);
Json::Value toJson(std::unordered_map<h256, LocalisedLogEntries> const& _entriesByBlock);
Json::Value toJsonByBlock(LocalisedLogEntries const& _entries);
TransactionSkeleton toTransactionSkeleton(Json::Value const& _json);
LogFilter toLogFilter(Json::Value const& _json);
LogFilter toLogFilter(Json::Value const& _json, Interface const& _client);  // commented to avoid warning. Uncomment once in use @ PoC-7.

class AddressResolver
{
public:
    static Address fromJS(std::string const& _address);
};

#endif //LIBWEB3CRPC_JSONHELPER_CIC_H
