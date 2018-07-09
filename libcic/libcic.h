#ifndef LIBCIC_LIBCIC_H
#define LIBCIC_LIBCIC_H

#include <libcolcrypto/libcolcrypto.h>
#include <libcolcore/libcolcore.h>
#include <libcicore/libcicore.h>
#include <libcvm/libcvm.h>
#include <json_spirit/JsonSpiritHeaders.h>

//C++ standard
#include <exception>
#include <array>
#include <functional>
#include <map>

//C++ boost
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/timer.hpp>

//Json library
#include <json/json.h>

namespace CI
{
    namespace cic
    {
        using namespace CI::col;

        #include "Defaults.h"
        #include "CodeSizeCache.h"
        #include "LastBlockHashesFace.h"

        #include "GasPricer.h"
        #include "TransactionReceipt.h"
        #include "Transaction.h"

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
        #include "State.h"
        #include "ExtVM.h"
        #include "Executive.h"
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
