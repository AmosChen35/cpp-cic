
set(sources
    libcnet.cpp libcnet.h
    Common.cpp Common.h
    Network.cpp Network.h
    Session.cpp Session.h

    HostCapability.cpp HostCapability.h
    Capability.cpp Capability.h
    Host.cpp Host.h
)

add_library(cnet ${sources})

target_include_directories(cnet PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(cnet PUBLIC colcrypto colcore)
