#include "libcic.h"

using namespace CI;
using namespace CI::col;
using namespace CI::cic;

void Interface::submitTransaction(Secret const& _secret, u256 const& _value, Address const& _dest, bytes const& _data, u256 const& _gas, u256 const& _gasPrice, u256 const& _nonce)
{
    TransactionSkeleton ts;
    ts.creation = false;
    ts.value = _value;
    ts.to = _dest;
    ts.data = _data;
    ts.gas = _gas;
    ts.gasPrice = _gasPrice;
    ts.nonce = _nonce;
    submitTransaction(ts, _secret);
}

Address Interface::submitTransaction(Secret const& _secret, u256 const& _endowment, bytes const& _init, u256 const& _gas, u256 const& _gasPrice, u256 const& _nonce)
{
    TransactionSkeleton ts;
    ts.creation = true;
    ts.value = _endowment;
    ts.data = _init;
    ts.gas = _gas;
    ts.gasPrice = _gasPrice;
    ts.nonce = _nonce;
    return submitTransaction(ts, _secret).second;
}

BlockHeader Interface::blockInfo(BlockNumber _block) const
{
    if (_block == PendingBlock)
        return pendingInfo();
    return blockInfo(hashFromNumber(_block));
}

//FIXME
/*
BlockDetails Interface::blockDetails(BlockNumber _block) const
{
    if (_block == PendingBlock)
        return pendingDetails();
    return blockDetails(hashFromNumber(_block));
}
*/
