
set(sources
    libcicore.cpp libcicore.h
    Exceptions.h
    Common.cpp Common.h
    CommonJS.cpp CommonJS.h
    EVMSchedule.h
    TransactionBase.cpp TransactionBase.h
    LogEntry.cpp LogEntry.h

    Precompiled.cpp Precompiled.h
    ChainOperationParams.cpp ChainOperationParams.h
    BlockHeader.cpp BlockHeader.h

    SealEngine.cpp SealEngine.h
)

add_library(cicore ${sources})

target_include_directories(cicore PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(cicore PUBLIC colcrypto colcore)
