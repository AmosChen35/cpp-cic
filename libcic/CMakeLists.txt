
set(sources
    libcic.cpp libcic.h

    Defaults.cpp Defaults.h
    CodeSizeCache.h
    LastBlockHashesFace.h

    GasPricer.cpp GasPricer.h
    TransactionReceipt.cpp TransactionReceipt.h
    Transaction.cpp Transaction.h

    LogFilter.cpp LogFilter.h
    Account.cpp Account.h

    GenesisInfo.cpp GenesisInfo.h
    ChainParams.cpp ChainParams.h

    Interface.cpp Interface.h
    State.cpp State.h
    ExtVM.cpp ExtVM.h
    Executive.cpp Executive.h
)

add_library(cic ${sources})

target_include_directories(cic PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(cic PUBLIC cvm cicore colcrypto colcore PRIVATE jsoncpp_lib_static Boost::fiber Boost::context)
