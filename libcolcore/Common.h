#ifndef LIBCOLCORE_COMMON_H
#define LIBCOLCORE_COMMON_H

using namespace boost::multiprecision::literals;

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

#endif //LIBCOLCORE_COMMON_H
