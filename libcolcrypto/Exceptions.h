#ifndef LIBCOLCRYPTO_EXCEPTIONS_H
#define LIBCOLCRYPTO_EXCEPTIONS_H

namespace crypto
{

/// Rare malfunction of cryptographic functions.
DEV_SIMPLE_EXCEPTION(CryptoException);

}

#endif //LIBCOLCRYPTO_EXCEPTIONS_H
