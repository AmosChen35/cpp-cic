#ifndef LIBCVM_LIBCVM_H
#define LIBCVM_LIBCVM_H

#include <libcolcore/libcolcore.h>
#include <libcicore/libcicore.h>

//C++ standard
#include <functional>
#include <set>
#include <memory>

//C++ boost library
#include <boost/optional.hpp>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <boost/program_options/options_description.hpp>

namespace CI
{
    namespace cic
    {
        using namespace CI::col;

        #include "evmc/evmc.h"
        #include "interpreter.h"
        #include "Instruction.h"
        #include "ExtVMFace.h"
        #include "VMConfig.h"
        #include "VMFace.h"
        #include "LegacyVM.h"
        #include "VMFactory.h"
    }
}

#endif //#define LIBCVM_LIBCVM_H
