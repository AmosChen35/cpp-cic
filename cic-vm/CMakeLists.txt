
add_executable(cic-vm main.cpp)

target_link_libraries(cic-vm PRIVATE cic-buildinfo web3crpc web3agent cihashseal cnet cic cvm cicore colcore colcrypto json_spirit Boost::program_options)

install(TARGETS cic-vm EXPORT alethTargets DESTINATION bin)
