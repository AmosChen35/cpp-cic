#ifndef LIBCIHASHSEAL_LIBCIHASHSEAL_H
#define LIBCIHASHSEAL_LIBCIHASHSEAL_H

#include <libcolcore/libcolcore.h>
#include <libcicore/libcicore.h>
#include <libcic/libcic.h>
#include <ethash/ethash.hpp>
#include <json_spirit/JsonSpiritHeaders.h>

//C++ standard
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <tuple>

//C++ boost
#include <boost/filesystem/path.hpp>

//Json library
#include <json/json.h>

namespace CI
{
    namespace cic
    {
        using namespace CI::col;

        #include "libcihashseal.h"
        #include "GenesisInfo.h"

        #include "EthashProofOfWork.h"
        #include "EthashCPUMiner.h"
        #include "Ethash.h"
        #include "EthashClient.h"
    }
}

#endif //LIBCIHASHSEAL_LIBCIHASHSEAL_H
