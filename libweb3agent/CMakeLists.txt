
set(sources
    libweb3agent.cpp libweb3agent.h
    WebThree.cpp WebThree.h
)

add_library(web3agent ${sources})

target_include_directories(web3agent PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(web3agent PUBLIC cic cicore cnet cihashseal cic-buildinfo)
