
set(sources
    libcic.cpp libcic.h

    GenericMiner.h
    GenericFarm.h

    Defaults.cpp Defaults.h
    CommonNet.cpp CommonNet.h
    CodeSizeCache.h
    LastBlockHashesFace.h
    ImportPerformanceLogger.cpp ImportPerformanceLogger.h
    GasPricer.cpp GasPricer.h

    TransactionReceipt.cpp TransactionReceipt.h
    Transaction.cpp Transaction.h
    TransactionQueue.cpp TransactionQueue.h

    VerifiedBlock.h
    BlockDetails.cpp BlockDetails.h

    LogFilter.cpp LogFilter.h
    Account.cpp Account.h

    GenesisInfo.cpp GenesisInfo.h
    ChainParams.cpp ChainParams.h

    Interface.cpp Interface.h

    BasicAuthority.cpp BasicAuthority.h

    State.cpp State.h
    ExtVM.cpp ExtVM.h
    Executive.cpp Executive.h

    Block.cpp Block.h
    BlockQueue.cpp BlockQueue.h
    BlockChain.cpp BlockChain.h

    EthereumPeer.cpp EthereumPeer.h
    EthereumHost.cpp EthereumHost.h

    ClientBase.cpp ClientBase.h
    Client.cpp Client.h
    ClientTest.cpp ClientTest.h
)

add_library(cic ${sources})

target_include_directories(cic PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(cic PUBLIC cnet cvm cicore colcrypto colcore PRIVATE jsoncpp_lib_static Boost::fiber Boost::context)
