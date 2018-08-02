#ifndef LIBCNET_LIBCNET_H
#define LIBCNET_LIBCNET_H

#include <libcolcore/libcolcore.h>
#include <libcolcrypto/libcolcrypto.h>

//C++ standard
#include <atomic>
#include <string>
#include <set>
#include <vector>
#include <chrono>
#include <memory>
#include <deque>
#include <array>
#include <sys/types.h>
#ifndef _WIN32
#include <ifaddrs.h>
#endif
#include <mutex>
#include <map>
#include <utility>
#include <thread>


//C++ boost
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace ba = boost::asio;
namespace bi = boost::asio::ip;

namespace CI
{
    namespace cnet
    {
        using namespace CI::col;

        #include "Common.h"
        #include "RLPXSocket.h"
        #include "Network.h"
        #include "Session.h"
    }
}

/// std::hash for asio::adress
namespace std
{

template <> struct hash<bi::address>
{
    size_t operator()(bi::address const& _a) const
    {
        if (_a.is_v4())
            return std::hash<unsigned long>()(_a.to_v4().to_ulong());
        if (_a.is_v6())
        {
            auto const& range = _a.to_v6().to_bytes();
            return boost::hash_range(range.begin(), range.end());
        }
        if (_a.is_unspecified())
            return static_cast<size_t>(0x3487194039229152ull);  // Chosen by fair dice roll, guaranteed to be random
        return std::hash<std::string>()(_a.to_string());
    }
};

template<> struct hash<pair<CI::cnet::NodeID, string>>
{
    size_t operator()(pair<CI::cnet::NodeID, string> const& _value) const
    {
        size_t ret = hash<CI::cnet::NodeID>()(_value.first);
        return ret ^ (hash<string>()(_value.second) + 0x9e3779b9 + (ret << 6) + (ret >> 2));
    }
};

}

namespace CI
{
    namespace cnet
    {
        #include "HostCapability.h"
        #include "Capability.h"
        #include "Host.h"
    }
}


#endif //LIBCNET_LIBCNET_H
