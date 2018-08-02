
set(sources
    libcihashseal.cpp libcihashseal.h
    GenesisInfo.cpp GenesisInfo.h

    EthashProofOfWork.cpp EthashProofOfWork.h
    EthashCPUMiner.cpp EthashCPUMiner.h
    Ethash.cpp Ethash.h
    EthashClient.cpp EthashClient.h
)

add_library(cihashseal ${sources})

target_include_directories(cihashseal PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(cihashseal PUBLIC cic cicore colcore)
