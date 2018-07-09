#ifndef LIBCOLCRYPTO_HASH_H
#define LIBCOLCRYPTO_HASH_H

h256 sha256(bytesConstRef _input) noexcept;

h160 ripemd160(bytesConstRef _input);

#endif //LIBCOLCRYPTO_HASH_H
