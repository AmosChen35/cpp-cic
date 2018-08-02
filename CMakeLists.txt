#------------------------------------------------------------------------------
# Top-level CMake file for CIC.
#
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5.1)

# Default cmake modules.
include(GNUInstallDirs)

set(CIC_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")

set(CPP_CIC_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to the root directory for CIC")

# Toolchian setup
add_compile_options(-std=c++11)
add_compile_options(-fext-numeric-literals)
set(TOOLCHAIN cxx11)
set(toolchain_dir ${CIC_CMAKE_DIR}/toolchains)
set(toolchain_file ${toolchain_dir}/${TOOLCHAIN}.cmake)
set(CMAKE_TOOLCHAIN_FILE ${toolchain_file} CACHE FILEPATH "CMake toolchain file")

list(APPEND CMAKE_MODULE_PATH ${CIC_CMAKE_DIR})

# Map current configuration to configurations of imported targets.
set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG Release)
set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)

# CMake driven cross-platform package management for C/C++.
#set(HUNTER_CONFIGURATION_TYPES Release)
#set(HUNTER_JOBS_NUMBER 4)
#set(HUNTER_CACHE_SERVERS "https://github.com/ethereum/hunter-cache")
#set(HUNTER_PASSWORDS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Hunter/passwords.cmake)

# In CI builds upload the binaries if the GITHUB_USER_PASSWORD was decrypted
# (only for branches and internal PRs).
if("$ENV{CI}" AND NOT "$ENV{GITHUB_USER_PASSWORD}" STREQUAL "")
    set(run_upload YES)
else()
    set(run_upload NO)
endif()
#option(HUNTER_RUN_UPLOAD "Upload binaries to the cache server" ${run_upload})

include("${CIC_CMAKE_DIR}/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.22.16.tar.gz"
    SHA1 "84153076a3cebf4869c904fa5c93ea309386b583"
    LOCAL
)

project(cpp-cic)
set(PROJECT_VERSION 0.1.0.dev0)

include(BuildInfo)
cable_add_buildinfo_library(PREFIX cic)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY On)

include(EthOptions)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
hunter_add_package(Boost COMPONENTS program_options filesystem system thread context fiber log)
find_package(Boost CONFIG REQUIRED program_options filesystem system thread context fiber log)

hunter_add_package(ethash)
find_package(ethash CONFIG REQUIRED)

hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

hunter_add_package(cryptopp)
find_package(cryptopp CONFIG REQUIRED)

hunter_add_package(libjson-rpc-cpp)
find_package(libjson-rpc-cpp CONFIG REQUIRED)

hunter_add_package(libscrypt)
find_package(libscrypt CONFIG REQUIRED)

#LevelDB library
include(FindLevelDB)
find_package(LevelDB)

#Crypto library
include(ProjectSecp256k1)
include(ProjectLibFF)

configure_project()

#Global include path for all libs.
include_directories("${CMAKE_SOURCE_DIR}")

add_subdirectory(json_spirit)

add_subdirectory(libcolcore)
add_subdirectory(libcolcrypto)
add_subdirectory(libcnet)
add_subdirectory(libcicore)
add_subdirectory(libcvm)
add_subdirectory(libcic)
add_subdirectory(libcihashseal)

add_subdirectory(libweb3agent)
add_subdirectory(libweb3crpc)

add_subdirectory(cic-vm)
