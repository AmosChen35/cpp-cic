#ifndef LIBWEB3CRPC_LIBWEB3CRPC_H
#define LIBWEB3CRPC_LIBWEB3CRPC_H

#include <libcolcore/libcolcore.h>
#include <libcicore/libcicore.h>
#include <libcic/libcic.h>
#include <libcnet/libcnet.h>
#include <libweb3agent/libweb3agent.h>

//C++ standard
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <functional>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <iosfwd>
#include <csignal>
#include <atomic>
#include <fcntl.h>
#include <unistd.h>

//C++ boost
#include <boost/filesystem/path.hpp>

//Json library
#include <json/json.h>

//Cpp jsonrpc
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/common/exception.h>
#include <jsonrpccpp/common/procedure.h>
#include <jsonrpccpp/server/abstractserverconnector.h>
#include <jsonrpccpp/server/iprocedureinvokationhandler.h>
#include <jsonrpccpp/server/requesthandlerfactory.h>

namespace CI
{
    namespace col
    {
        #include "JsonHelper_col.h"
    }

    namespace cic
    {
        #include "JsonHelper_cic.h"
    }

    namespace cnet
    {
        #include "JsonHelper_cnet.h"
    }

    namespace crpc
    {
        using namespace CI::col;

        #include "JsonHelper_crpc.h"
    }
}

namespace CI
{
    namespace crpc
    {
        enum class Privilege
        {
            Admin
        };
    }
}

namespace std
{
    template<> struct hash<CI::crpc::Privilege>
    {
        size_t operator()(CI::crpc::Privilege _value) const { return (size_t)_value; }
    };
}

namespace CI
{
    namespace col
    {
        #include "IpcServerBase.h"
        #include "IpcServer.h"
    }

    namespace cic
    {
        #include "AccountHolder.h"

        #include "StandardTrace.h"
    }

    namespace crpc
    {
        #include "ModularServer.h"
        #include "SessionManager.h"

        #include "EthFace.h"
        #include "Eth.h"

        #include "AdminNetFace.h"
        #include "AdminNet.h"

        #include "Web3Face.h"
        #include "Web3.h"

        #include "PersonalFace.h"
        #include "Personal.h"

        #include "AdminEthFace.h"
        #include "AdminEth.h"

        #include "DebugFace.h"
        #include "Debug.h"

        #include "TestFace.h"
        #include "Test.h"

        #include "NetFace.h"
        #include "Net.h"
    }
}

#endif //LIBWEB3CRPC_LIBWEB3CRPC_H
