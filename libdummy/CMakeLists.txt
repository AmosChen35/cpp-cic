
set(sources
    libdummy.cpp libdummy.h
)

add_library(dummy ${sources})

target_include_directories(dummy PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(dummy PUBLIC cic cicore)
