#ifndef LIBWEB3AGENT_LIBWEB3AGENT_H
#define LIBWEB3AGENT_LIBWEB3AGENT_H

#include <libcicore/libcicore.h>
#include <libcic/libcic.h>
#include <libcihashseal/libcihashseal.h>
#include <libcnet/libcnet.h>
#include <cic-buildinfo.h>

//C++ standard
#include <thread>
#include <mutex>
#include <list>
#include <atomic>

//C++ boost
#include <boost/asio.hpp> // Make sure boost/asio.hpp is included before windows.h.
#include <boost/utility.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace CI
{
    namespace col
    {
        #include "WebThree.h"
    }
}

#endif //LIBWEB3AGENT_LIBWEB3AGENT_H
