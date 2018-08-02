#ifndef LIBCICORE_LIBCICORE_H
#define LIBCICORE_LIBCICORE_H

#include <libcolcore/libcolcore.h>
#include <libcolcrypto/libcolcrypto.h>
#include <json_spirit/JsonSpiritHeaders.h>

//C++ standard
#include <array>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <mutex>

//C++ boost
#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

namespace CI
{
    namespace cic
    {
        using namespace CI::col;

        #include "Exceptions.h"
        #include "Common.h"
        #include "CommonJS.h"
        #include "EVMSchedule.h"
        #include "TransactionBase.h"
        #include "LogEntry.h"

        //Assemble object of chain
        #include "Precompiled.h"
        #include "ChainOperationParams.h"
        #include "BlockHeader.h"

        //Seal
        #include "SealEngine.h"

        //Feature relational with key store.
        #include "KeyManager.h"
    }
}

#endif //LIBCICORE_LIBCICORE_H
