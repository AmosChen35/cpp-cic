#ifndef LIBCOLCRYPTO_LIBCOLCRYPTO_H
#define LIBCOLCRYPTO_LIBCOLCRYPTO_H

#include <libcolcore/libcolcore.h>

//C++ standard
#include <mutex>

//Crptopp
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/osrng.h>
#include <cryptopp/oids.h>

//Scrypt
#include <libscrypt.h>

//Secp256k1
#include <secp256k1.h>
#include <secp256k1_ecdh.h>
#include <secp256k1_recovery.h>
#include <secp256k1_sha256.h>

//Finite Field(FF)
#include <algebra/curves/alt_bn128/alt_bn128_g1.hpp>
#include <algebra/curves/alt_bn128/alt_bn128_g2.hpp>
#include <algebra/curves/alt_bn128/alt_bn128_pairing.hpp>
#include <algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <common/profiling.hpp>

namespace CI
{
    namespace col
    {
        #include "Exceptions.h"
        #include "Common.h"
        #include "AES.h"
        #include "CryptoPP.h"
        #include "Hash.h"
        #include "LibSnark.h"
    }
}

#endif //LIBCOLCRYPTO_LIBCOLCRYPTO_H
