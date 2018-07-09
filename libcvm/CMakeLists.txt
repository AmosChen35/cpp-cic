
set(sources
    libcvm.cpp libcvm.h
    evmc/evmc.h
    interpreter.h
    Instruction.cpp Instruction.h
    ExtVMFace.cpp ExtVMFace.h
    VMConfig.h
    VMFace.h
    LegacyVM.cpp LegacyVMCalls.cpp LegacyVMOpt.cpp LegacyVM.h
    VMFactory.cpp VMFactory.h
)

add_library(cvm ${sources})

target_link_libraries(cvm PUBLIC colcore cicore PRIVATE Boost::program_options ${CMAKE_DL_LIBS})
