#include "libweb3crpc.h"

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::crpc;

std::string Web3::web3_sha3(std::string const& _param1)
{
    return toJS(sha3(jsToBytes(_param1)));
}
