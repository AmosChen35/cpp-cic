#ifndef LIBCOLCORE_LIBCOLCORE_H
#define LIBCOLCORE_LIBCOLCORE_H

#if defined(_WIN32)
#include <shlobj.h>
#else
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#endif

#if defined(_WIN32)
#include <windows.h>
#else
#include <termios.h>
#endif

#ifdef __APPLE__
#include <pthread.h>
#endif

//Json library
#include <json_spirit/JsonSpiritHeaders.h>

//C++ standard
#include <string>
#include <sstream>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <atomic>
#include <array>
#include <list>
#include <vector>
#include <iosfwd>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <functional>
#include <chrono>
#include <exception>
#include <type_traits>
#include <algorithm>
#include <random>
#include <iosfwd>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <thread>

//C++ boost
#include <boost/thread.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/info_tuple.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/core/null_deleter.hpp>

#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/function.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/exception_handler.hpp>

//Level DB
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

//Ethereum proof of work algorithm
#include <ethash/keccak.hpp>

namespace CI
{
    // CryptoPP defines byte in the global namespace, so must we.
    using byte = uint8_t;

    #define DEV_IGNORE_EXCEPTIONS(X) try { X; } catch (...) {}

    #define DEV_IF_THROWS(X) try{X;}catch(...)

    namespace col
    {
        #include "Assertions.h"
        #include "vector_ref.h"
        #include "Terminal.h"
        #include "Common.h"
        #include "CommonData.h"
        #include "FixedHash.h"
        #include "Exceptions.h"
        #include "Log.h"
        #include "RLP.h"
        #include "SHA3.h"
        #include "FileSystem.h"
        #include "CommonIO.h"
        #include "CommonJS.h"
        #include "Address.h"
        #include "Guards.h"
        #include "Base64.h"
    }
}

//FixHash.h
namespace std
{
    /// Forward std::hash<col::FixedHash> to col::FixedHash::hash.
    template<> struct hash<CI::col::h64>: CI::col::h64::hash {};
    template<> struct hash<CI::col::h128>: CI::col::h128::hash {};
    template<> struct hash<CI::col::h160>: CI::col::h160::hash {};
    template<> struct hash<CI::col::h256>: CI::col::h256::hash {};
    template<> struct hash<CI::col::h512>: CI::col::h512::hash {};
}

namespace CI
{
    namespace col
    {
        #include "dbfwd.h"
        #include "db.h"

        //LevelDB
        #include "LevelDB.h"
        #include "DBImpl.h"

        //OverlayDB
        #include "TrieCommon.h"
        #include "TrieDB.h"
        #include "TrieHash.h"
        #include "MemoryDB.h"
        #include "OverlayDB.h"

        #include "JsonUtils.h"
    }
}

#endif //LIBCOLCORE_LIBCOLCORE_H
