#ifndef LIBCOLCRYPTO_CRYPTOPP_H
#define LIBCOLCRYPTO_CRYPTOPP_H

namespace crypto
{
/// Amount of bytes added when encrypting with encryptECIES.
static const unsigned c_eciesOverhead = 113;

/**
 * CryptoPP secp256k1 algorithms.
 * @todo Collect ECIES methods into class.
 */
class Secp256k1PP
{
public:
    static Secp256k1PP* get();

    /// Encrypts text (replace input). (ECIES w/XOR-SHA1)
    void encrypt(Public const& _k, bytes& io_cipher);

    /// Decrypts text (replace input). (ECIES w/XOR-SHA1)
    void decrypt(Secret const& _k, bytes& io_text);

    /// Encrypts text (replace input). (ECIES w/AES128-CTR-SHA256)
    void encryptECIES(Public const& _k, bytes& io_cipher);

    /// Encrypts text (replace input). (ECIES w/AES128-CTR-SHA256)
    void encryptECIES(Public const& _k, bytesConstRef _sharedMacData, bytes& io_cipher);

    /// Decrypts text (replace input). (ECIES w/AES128-CTR-SHA256)
    bool decryptECIES(Secret const& _k, bytes& io_text);

    /// Decrypts text (replace input). (ECIES w/AES128-CTR-SHA256)
    bool decryptECIES(Secret const& _k, bytesConstRef _sharedMacData, bytes& io_text);

private:
    Secp256k1PP() = default;
};

} //namepspace crypto

class Secp256k1PPCtx
{
public:
    CryptoPP::OID m_oid;

    std::mutex x_rng;
    CryptoPP::AutoSeededRandomPool m_rng;

    std::mutex x_params;
    CryptoPP::DL_GroupParameters_EC<CryptoPP::ECP> m_params;

    CryptoPP::DL_GroupParameters_EC<CryptoPP::ECP>::EllipticCurve m_curve;

    CryptoPP::Integer m_q;
    CryptoPP::Integer m_qs;

    static Secp256k1PPCtx& get()
    {
        static Secp256k1PPCtx ctx;
        return ctx;
    }

private:
    Secp256k1PPCtx():
        m_oid(CryptoPP::ASN1::secp256k1()), m_params(m_oid), m_curve(m_params.GetCurve()),
        m_q(m_params.GetGroupOrder()), m_qs(m_params.GetSubgroupOrder())
    {}
};

#endif //LIBCOLCRYPTO_CRYPTOPP_H

