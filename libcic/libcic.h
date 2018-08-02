#ifndef LIBCIC_LIBCIC_H
#define LIBCIC_LIBCIC_H

#include <libcolcrypto/libcolcrypto.h>
#include <libcolcore/libcolcore.h>
#include <libcicore/libcicore.h>
#include <libcvm/libcvm.h>
#include <libcnet/libcnet.h>
#include <json_spirit/JsonSpiritHeaders.h>

//C++ standard
#include <algorithm>
#include <exception>
#include <array>
#include <functional>
#include <map>
#include <string>
#include <chrono>
#include <ctime>
#include <condition_variable>
#include <thread>
#include <deque>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <mutex>
#include <memory>
#include <utility>
#include <list>
#include <atomic>

//C++ boost
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/timer.hpp>
#include <boost/exception/errinfo_nested_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/fiber/all.hpp>

//Json library
#include <json/json.h>

namespace CI
{
    namespace cic
    {
        using namespace CI::col;

        #include "GenericMiner.h"
        #include "GenericFarm.h"

        #include "Defaults.h"
        #include "CommonNet.h"
        #include "CodeSizeCache.h"
        #include "LastBlockHashesFace.h"
        #include "ImportPerformanceLogger.h"
        #include "GasPricer.h"

        #include "TransactionReceipt.h"
        #include "Transaction.h"
        #include "TransactionQueue.h"

        #include "VerifiedBlock.h"
        #include "BlockDetails.h"

        #include "LogFilter.h"
        #include "Account.h"

        #include "GenesisInfo.h"
        #include "ChainParams.h"

        class Watch;
    }
}

namespace std
{
    void swap(CI::cic::Watch& _a, CI::cic::Watch& _b);

    template <> struct hash<pair<CI::col::h256, unsigned>>
    {
        size_t operator()(pair<CI::col::h256, unsigned> const& _x) const
        {
            return hash<CI::col::h256>()(_x.first) ^ hash<unsigned>()(_x.second);
        }
    };
}

namespace Json
{
    class Value;
}

namespace CI
{
    namespace cic
    {
        #include "Interface.h"

        #include "BasicAuthority.h"

        #include "State.h"
        #include "ExtVM.h"
        #include "Executive.h"

        #include "Block.h"
        #include "BlockQueue.h"
        #include "BlockChain.h"

        #include "EthereumPeer.h"
        #include "EthereumHost.h"

        #include "ClientBase.h"
        #include "Client.h"
        #include "ClientTest.h"
    }
}

namespace std
{
    inline void swap(CI::cic::Watch& _a, CI::cic::Watch& _b)
    {
        swap(_a.m_c, _b.m_c);
        swap(_a.m_id, _b.m_id);
    }
}

#endif //LIBCIC_LIBCIC_H
