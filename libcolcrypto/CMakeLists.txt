
set(sources
    libcolcrypto.cpp libcolcrypto.h
    Common.h Common.cpp
    AES.cpp AES.h
    CryptoPP.cpp CryptoPP.h
    Hash.cpp Hash.h
    LibSnark.cpp LibSnark.h
)

add_library(colcrypto ${sources})

target_include_directories(colcrypto PUBLIC ${Boost_INCLUDE_DIR} ${libff_inlcude_dir})

target_link_libraries(colcrypto PUBLIC colcore Secp256k1 PRIVATE libff::ff cryptopp-static libscrypt::scrypt)
