#ifndef LIBCOLCORE_LOG_H
#define LIBCOLCORE_LOG_H

void setThreadName(std::string const& _n);

/// Set the current thread's log name.
std::string getThreadName();

#define LOG BOOST_LOG

enum Verbosity
{
    VerbositySilent = -1,
    VerbosityError = 0,
    VerbosityWarning = 1,
    VerbosityInfo = 2,
    VerbosityDebug = 3,
    VerbosityTrace = 4,
};

// Simple cout-like stream objects for accessing common log channels.
// Thread-safe
BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(g_errorLogger,
    boost::log::sources::severity_channel_logger_mt<>,
    (boost::log::keywords::severity = VerbosityError)(boost::log::keywords::channel = "error"))
#define cerror LOG(CI::col::g_errorLogger::get())

BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(g_warnLogger,
    boost::log::sources::severity_channel_logger_mt<>,
    (boost::log::keywords::severity = VerbosityWarning)(boost::log::keywords::channel = "warn"))
#define cwarn LOG(CI::col::g_warnLogger::get())

BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(g_noteLogger,
    boost::log::sources::severity_channel_logger_mt<>,
    (boost::log::keywords::severity = VerbosityInfo)(boost::log::keywords::channel = "info"))
#define cnote LOG(CI::col::g_noteLogger::get())

BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(g_debugLogger,
    boost::log::sources::severity_channel_logger_mt<>,
    (boost::log::keywords::severity = VerbosityDebug)(boost::log::keywords::channel = "debug"))
#define cdebug LOG(CI::col::g_debugLogger::get())

BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(g_traceLogger,
    boost::log::sources::severity_channel_logger_mt<>,
    (boost::log::keywords::severity = VerbosityTrace)(boost::log::keywords::channel = "trace"))
#define ctrace LOG(CI::col::g_traceLogger::get())

// Simple macro to log to any channel a message without creating a logger object
// e.g. clog(VerbosityInfo, "channel") << "message";
// Thread-safe
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(
    g_clogLogger, boost::log::sources::severity_channel_logger_mt<>);
#define clog(SEVERITY, CHANNEL)                            \
    BOOST_LOG_STREAM_WITH_PARAMS(CI::col::g_clogLogger::get(), \
        (boost::log::keywords::severity = SEVERITY)(boost::log::keywords::channel = CHANNEL))


struct LoggingOptions
{
    int verbosity = VerbosityInfo;
    strings includeChannels;
    strings excludeChannels;
};

// Should be called in every executable
void setupLogging(LoggingOptions const& _options);

// Simple non-thread-safe logger with fixed severity and channel for each message
using Logger = boost::log::sources::severity_channel_logger<>;
inline Logger createLogger(int _severity, std::string const& _channel)
{
    return Logger(
        boost::log::keywords::severity = _severity, boost::log::keywords::channel = _channel);
}

// Adds the context string to all log messages in the scope
#define LOG_SCOPED_CONTEXT(context) \
    BOOST_LOG_SCOPED_THREAD_ATTR("Context", boost::log::attributes::constant<std::string>(context));


// Below overloads for both const and non-const references are needed, because without overload for
// non-const reference generic operator<<(formatting_ostream& _strm, T& _value) will be preferred by
// overload resolution.
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, bigint const& _value)
{
    _strm.stream() << EthNavy << _value << EthReset;
    return _strm;
}
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, bigint& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, u256 const& _value)
{
    _strm.stream() << EthNavy << _value << EthReset;
    return _strm;
}
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, u256& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, u160 const& _value)
{
    _strm.stream() << EthNavy << _value << EthReset;
    return _strm;
}
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, u160& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

template <unsigned N>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, FixedHash<N> const& _value)
{
    _strm.stream() << EthTeal "#" << _value.abridged() << EthReset;
    return _strm;
}
template <unsigned N>
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, FixedHash<N>& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, h160 const& _value)
{
    _strm.stream() << EthRed "@" << _value.abridged() << EthReset;
    return _strm;
}
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, h160& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, h256 const& _value)
{
    _strm.stream() << EthCyan "#" << _value.abridged() << EthReset;
    return _strm;
}
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, h256& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, h512 const& _value)
{
    _strm.stream() << EthTeal "##" << _value.abridged() << EthReset;
    return _strm;
}
inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, h512& _value)
{
    auto const& constValue = _value;
    _strm << constValue;
    return _strm;
}

inline boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& _strm, bytesConstRef _value)
{
    _strm.stream() << EthYellow "%" << toHex(_value) << EthReset;
    return _strm;
}

#endif //LIBCOLCORE_LOG_H
