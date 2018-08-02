
set(sources
    libweb3crpc.cpp libweb3crpc.h

    JsonHelper_col.cpp JsonHelper_col.h
    JsonHelper_cic.cpp JsonHelper_cic.h
    JsonHelper_cnet.cpp JsonHelper_cnet.h
    JsonHelper_crpc.cpp JsonHelper_crpc.h

    IpcServerBase.cpp IpcServerBase.h

    AccountHolder.cpp AccountHolder.h

    StandardTrace.cpp StandardTrace.h

    ModularServer.h
    SessionManager.cpp SessionManager.h

    EthFace.h
    Eth.cpp Eth.h

    AdminNetFace.h
    AdminNet.cpp AdminNet.h

    Web3Face.h
    Web3.cpp Web3.h

    PersonalFace.h
    Personal.cpp Personal.h

    AdminEthFace.h
    AdminEth.cpp AdminEth.h

    DebugFace.h
    Debug.cpp Debug.h

    TestFace.h
    Test.cpp Test.h

    NetFace.h
    Net.cpp Net.h
)

if(WIN32)
    list(APPEND sources WinPipeServer.cpp WinPipeServer.h)
else()
    list(APPEND sources UnixSocketServer.cpp UnixSocketServer.h)
endif()

add_library(web3crpc ${sources})

target_include_directories(web3crpc PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(web3crpc web3agent cihashseal cnet cic cicore colcore libjson-rpc-cpp::server)
