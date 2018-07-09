#include "libcolcore.h"

using namespace CI;
using namespace CI::col;

namespace CI
{
namespace col
{

/// Associate a name with each thread for nice logging.
struct ThreadLocalLogName
{
    ThreadLocalLogName(std::string const& _name) { m_name.reset(new std::string(_name)); }
    boost::thread_specific_ptr<std::string> m_name;
};

ThreadLocalLogName g_logThreadName("main");
}  // namespace

std::string getThreadName()
{
#if defined(__GLIBC__) || defined(__APPLE__)
    char buffer[128];
    pthread_getname_np(pthread_self(), buffer, 127);
    buffer[127] = 0;
    return buffer;
#else
    return g_logThreadName.m_name.get() ? *g_logThreadName.m_name.get() : "<unknown>";
#endif
}

void setThreadName(std::string const& _n)
{
#if defined(__GLIBC__)
    pthread_setname_np(pthread_self(), _n.c_str());
#elif defined(__APPLE__)
    pthread_setname_np(_n.c_str());
#else
    g_logThreadName.m_name.reset(new std::string(_n));
#endif
}

BOOST_LOG_ATTRIBUTE_KEYWORD(channel, "Channel", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(context, "Context", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(threadName, "ThreadName", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)

void setupLogging(LoggingOptions const& _options)
{
    auto sink = boost::make_shared<
        boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend>>();

    boost::shared_ptr<std::ostream> stream{&std::cout, boost::null_deleter{}};
    sink->locked_backend()->add_stream(stream);
    sink->set_filter([_options](boost::log::attribute_value_set const& _set) {
        if (_set["Severity"].extract<int>() > _options.verbosity)
            return false;

        auto const messageChannel = _set[channel];
        return (_options.includeChannels.empty() ||
                   contains(_options.includeChannels, messageChannel)) &&
               !contains(_options.excludeChannels, messageChannel);
    });

    namespace expr = boost::log::expressions;
    sink->set_formatter(expr::stream
                        << EthViolet << expr::format_date_time(timestamp, "%Y-%m-%d %H:%M:%S")
                        << EthReset " " EthNavy << threadName << EthReset " " << channel
                        << expr::if_(expr::has_attr(
                               context))[expr::stream << " " EthNavy << context << EthReset]
                        << " " << expr::smessage);

    boost::log::core::get()->add_sink(sink);

    boost::log::core::get()->add_global_attribute(
        "ThreadName", boost::log::attributes::make_function(&getThreadName));
    boost::log::core::get()->add_global_attribute(
        "TimeStamp", boost::log::attributes::local_clock());

    boost::log::core::get()->set_exception_handler(
        boost::log::make_exception_handler<std::exception>([](std::exception const& _ex) {
        std::cerr << "Exception from the logging library: " << _ex.what() << '\n';
    }));

} //namespace col
} //namespace CIC

namespace boost
{
namespace log
{

inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, bytes const& _value)
{
    _strm.stream() << EthYellow "%" << toHex(_value) << EthReset;
    return _strm;
}
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, bytes& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

template <typename T>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::vector<T> const& _value)
{
    _strm.stream() << EthWhite "[" EthReset;
    int n = 0;
    for (T const& i : _value)
    {
        _strm.stream() << (n++ ? EthWhite ", " EthReset : "");
        _strm << i;
    }
    _strm.stream() << EthWhite "]" EthReset;
    return _strm;
}
template <typename T>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::vector<T>& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

template <typename T>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::set<T> const& _value)
{
    _strm.stream() << EthYellow "{" EthReset;
    int n = 0;
    for (T const& i : _value)
    {
        _strm.stream() << (n++ ? EthYellow ", " EthReset : "");
        _strm << i;
    }
    _strm.stream() << EthYellow "}" EthReset;
    return _strm;
}
template <typename T>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::set<T>& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

template <typename T>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::unordered_set<T> const& _value)
{
    _strm.stream() << EthYellow "{" EthReset;
    int n = 0;
    for (T const& i : _value)
    {
        _strm.stream() << (n++ ? EthYellow ", " EthReset : "");
        _strm << i;
    }
    _strm.stream() << EthYellow "}" EthReset;
    return _strm;
}
template <typename T>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::unordered_set<T>& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

template <typename T, typename U>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::map<T, U> const& _value)
{
    _strm.stream() << EthLime "{" EthReset;
    int n = 0;
    for (auto const& i : _value)
    {
        _strm << (n++ ? EthLime ", " EthReset : "");
        _strm << i.first;
        _strm << (n++ ? EthLime ": " EthReset : "");
        _strm << i.second;
    }
    _strm.stream() << EthLime "}" EthReset;
    return _strm;
}
template <typename T, typename U>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::map<T, U>& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

template <typename T, typename U>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::unordered_map<T, U> const& _value)
{
    _strm << EthLime "{" EthReset;
    int n = 0;
    for (auto const& i : _value)
    {
        _strm.stream() << (n++ ? EthLime ", " EthReset : "");
        _strm << i.first;
        _strm.stream() << (n++ ? EthLime ": " EthReset : "");
        _strm << i.second;
    }
    _strm << EthLime "}" EthReset;
    return _strm;
}
template <typename T, typename U>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::unordered_map<T, U>& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

template <typename T, typename U>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::pair<T, U> const& _value)
{
    _strm.stream() << EthPurple "(" EthReset;
    _strm << _value.first;
    _strm.stream() << EthPurple ", " EthReset;
    _strm << _value.second;
    _strm.stream() << EthPurple ")" EthReset;
    return _strm;
}
template <typename T, typename U>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, std::pair<T, U>& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}
} //namespace col
} //namespace CI
