#include "libweb3crpc.h"

using namespace std;
using namespace CI;
using namespace CI::col;

namespace CI
{
namespace crpc
{

h256 h256fromHex(string const& _s)
{
    try
    {
        return h256(_s);
    }
    catch (boost::exception const&)
    {
        throw jsonrpc::JsonRpcException("Invalid hex-encoded string: " + _s);
    }
}

} //namespace rpc
} //namespace CI
