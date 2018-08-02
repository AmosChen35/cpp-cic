#ifndef LIBCOLCORE_COMMON_H
#define LIBCOLCORE_COMMON_H

using namespace boost::multiprecision::literals;

extern char const* Version;
extern std::string const EmptyString;

// Binary data types.
using bytes = std::vector<byte>;
using bytesRef = vector_ref<byte>;
using bytesConstRef = vector_ref<byte const>;

// Binary secure data types.
using bytesSec = secure_vector<byte>;

// Numeric types.
using bigint = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<>>;
using u64 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<64, 64, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using u128 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<128, 128, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using u256 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<256, 256, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using s256 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<256, 256, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>;
using u160 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<160, 160, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using s160 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<160, 160, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>;
using u512 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<512, 512, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using s512 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<512, 512, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>;
using u256s = std::vector<u256>;
using u160s = std::vector<u160>;
using u256Set = std::set<u256>;
using u160Set = std::set<u160>;

// Map types.
using StringMap = std::map<std::string, std::string>;
using BytesMap = std::map<bytes, bytes>;
using u256Map = std::map<u256, u256>;
using HexMap = std::map<bytes, bytes>;

// Hash types.
using StringHashMap = std::unordered_map<std::string, std::string>;
using u256HashMap = std::unordered_map<u256, u256>;

// String types.
using strings = std::vector<std::string>;

// Fixed-length string types.
using string32 = std::array<char, 32>;

// Null/Invalid values for convenience.
extern bytes const NullBytes;
u256 constexpr Invalid256 =
    0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff_cppui256;

    /// Interprets @a _u as a two's complement signed number and returns the resulting s256.
inline s256 u2s(u256 _u)
{
    static const bigint c_end = bigint(1) << 256;
    if (boost::multiprecision::bit_test(_u, 255))
        return s256(-(c_end - _u));
    else
        return s256(_u);
}

/// @returns the two's complement signed representation of the signed number _u.
inline u256 s2u(s256 _u)
{
    static const bigint c_end = bigint(1) << 256;
    if (_u >= 0)
        return u256(_u);
    else
        return u256(c_end + _u);
}

/// Converts given int to a string and appends one of a series of units according to its size.

template <size_t n> inline u256 exp10()
{
    return exp10<n - 1>() * u256(10);
}

template <> inline u256 exp10<0>()
{
    return u256(1);
}

enum class WithExisting: int
{
    Trust = 0,
    Verify,
    Rescue,
    Kill
};

/// Inheritable for classes that have invariants.
class HasInvariants
{
public:
    /// Reimplement to specify the invariants.
    virtual bool invariants() const = 0;
};

/// RAII checker for invariant assertions.
class InvariantChecker
{
public:
    InvariantChecker(HasInvariants* _this, char const* _fn, char const* _file, int _line): m_this(_this), m_function(_fn), m_file(_file), m_line(_line) { checkInvariants(_this, _fn , _file, _line, true); }
    ~InvariantChecker() { checkInvariants(m_this, m_function, m_file, m_line, false); }
    /// Check invariants are met, throw if not.
    static void checkInvariants(HasInvariants const* _this, char const* _fn, char const* _file, int line, bool _pre);

private:
    HasInvariants const* m_this;
    char const* m_function;
    char const* m_file;
    int m_line;
};

/// Scope guard for invariant check in a class derived from HasInvariants.
#if ETH_DEBUG
#define DEV_INVARIANT_CHECK ::CI::col::InvariantChecker __dev_invariantCheck(this, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__)
#define DEV_INVARIANT_CHECK_HERE ::CI::col::InvariantChecker::checkInvariants(this, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__, true)
#else
#define DEV_INVARIANT_CHECK (void)0;
#define DEV_INVARIANT_CHECK_HERE (void)0;
#endif

/// Simple scope-based timer helper.
class TimerHelper
{
public:
    TimerHelper(std::string const& _id, unsigned _msReportWhenGreater = 0): m_t(std::chrono::high_resolution_clock::now()), m_id(_id), m_ms(_msReportWhenGreater) {}
    ~TimerHelper();

private:
    std::chrono::high_resolution_clock::time_point m_t;
    std::string m_id;
    unsigned m_ms;
};

class Timer
{
public:
    Timer() { restart(); }

    std::chrono::high_resolution_clock::duration duration() const { return std::chrono::high_resolution_clock::now() - m_t; }
    double elapsed() const { return std::chrono::duration_cast<std::chrono::microseconds>(duration()).count() / 1000000.0; }
    void restart() { m_t = std::chrono::high_resolution_clock::now(); }

private:
    std::chrono::high_resolution_clock::time_point m_t;
};

#define DEV_TIMED(S) for (::std::pair<::CI::col::TimerHelper, bool> __eth_t(S, true); __eth_t.second; __eth_t.second = false)
#define DEV_TIMED_SCOPE(S) ::CI::col::TimerHelper __eth_t(S)
#if defined(_WIN32)
#define DEV_TIMED_FUNCTION DEV_TIMED_SCOPE(__FUNCSIG__)
#else
#define DEV_TIMED_FUNCTION DEV_TIMED_SCOPE(__PRETTY_FUNCTION__)
#endif

#define DEV_TIMED_ABOVE(S, MS) for (::std::pair<::CI::col::TimerHelper, bool> __eth_t(::CI::col::TimerHelper(S, MS), true); __eth_t.second; __eth_t.second = false)
#define DEV_TIMED_SCOPE_ABOVE(S, MS) ::CI::col::TimerHelper __eth_t(S, MS)
#if defined(_WIN32)
#define DEV_TIMED_FUNCTION_ABOVE(MS) DEV_TIMED_SCOPE_ABOVE(__FUNCSIG__, MS)
#else
#define DEV_TIMED_FUNCTION_ABOVE(MS) DEV_TIMED_SCOPE_ABOVE(__PRETTY_FUNCTION__, MS)
#endif

/// Get the current time in seconds since the epoch in UTC
int64_t utcTime();

#endif //LIBCOLCORE_COMMON_H
