
add_executable(cic-vm main.cpp)

target_link_libraries(cic-vm PRIVATE cihashseal cic cvm cicore colcore colcrypto json_spirit Boost::program_options)

install(TARGETS cic-vm EXPORT alethTargets DESTINATION bin)
