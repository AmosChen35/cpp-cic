# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amoschen/workspace/cpp-cic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amoschen/workspace/cpp-cic/cic-vm

# Include any dependencies generated for this target.
include libcvm/CMakeFiles/cvm.dir/depend.make

# Include the progress variables for this target.
include libcvm/CMakeFiles/cvm.dir/progress.make

# Include the compile flags for this target's objects.
include libcvm/CMakeFiles/cvm.dir/flags.make

libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o: libcvm/CMakeFiles/cvm.dir/flags.make
libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o: ../libcvm/VMFactory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amoschen/workspace/cpp-cic/cic-vm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o"
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm.dir/VMFactory.cpp.o -c /home/amoschen/workspace/cpp-cic/libcvm/VMFactory.cpp

libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm.dir/VMFactory.cpp.i"
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amoschen/workspace/cpp-cic/libcvm/VMFactory.cpp > CMakeFiles/cvm.dir/VMFactory.cpp.i

libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm.dir/VMFactory.cpp.s"
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amoschen/workspace/cpp-cic/libcvm/VMFactory.cpp -o CMakeFiles/cvm.dir/VMFactory.cpp.s

libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.requires:

.PHONY : libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.requires

libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.provides: libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.requires
	$(MAKE) -f libcvm/CMakeFiles/cvm.dir/build.make libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.provides.build
.PHONY : libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.provides

libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.provides.build: libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o


libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o: libcvm/CMakeFiles/cvm.dir/flags.make
libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o: ../libcvm/libcvm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amoschen/workspace/cpp-cic/cic-vm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o"
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm.dir/libcvm.cpp.o -c /home/amoschen/workspace/cpp-cic/libcvm/libcvm.cpp

libcvm/CMakeFiles/cvm.dir/libcvm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm.dir/libcvm.cpp.i"
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amoschen/workspace/cpp-cic/libcvm/libcvm.cpp > CMakeFiles/cvm.dir/libcvm.cpp.i

libcvm/CMakeFiles/cvm.dir/libcvm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm.dir/libcvm.cpp.s"
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amoschen/workspace/cpp-cic/libcvm/libcvm.cpp -o CMakeFiles/cvm.dir/libcvm.cpp.s

libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.requires:

.PHONY : libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.requires

libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.provides: libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.requires
	$(MAKE) -f libcvm/CMakeFiles/cvm.dir/build.make libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.provides.build
.PHONY : libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.provides

libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.provides.build: libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o


# Object files for target cvm
cvm_OBJECTS = \
"CMakeFiles/cvm.dir/VMFactory.cpp.o" \
"CMakeFiles/cvm.dir/libcvm.cpp.o"

# External object files for target cvm
cvm_EXTERNAL_OBJECTS =

libcvm/libcvm.a: libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o
libcvm/libcvm.a: libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o
libcvm/libcvm.a: libcvm/CMakeFiles/cvm.dir/build.make
libcvm/libcvm.a: libcvm/CMakeFiles/cvm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amoschen/workspace/cpp-cic/cic-vm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcvm.a"
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && $(CMAKE_COMMAND) -P CMakeFiles/cvm.dir/cmake_clean_target.cmake
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cvm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libcvm/CMakeFiles/cvm.dir/build: libcvm/libcvm.a

.PHONY : libcvm/CMakeFiles/cvm.dir/build

libcvm/CMakeFiles/cvm.dir/requires: libcvm/CMakeFiles/cvm.dir/VMFactory.cpp.o.requires
libcvm/CMakeFiles/cvm.dir/requires: libcvm/CMakeFiles/cvm.dir/libcvm.cpp.o.requires

.PHONY : libcvm/CMakeFiles/cvm.dir/requires

libcvm/CMakeFiles/cvm.dir/clean:
	cd /home/amoschen/workspace/cpp-cic/cic-vm/libcvm && $(CMAKE_COMMAND) -P CMakeFiles/cvm.dir/cmake_clean.cmake
.PHONY : libcvm/CMakeFiles/cvm.dir/clean

libcvm/CMakeFiles/cvm.dir/depend:
	cd /home/amoschen/workspace/cpp-cic/cic-vm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amoschen/workspace/cpp-cic /home/amoschen/workspace/cpp-cic/libcvm /home/amoschen/workspace/cpp-cic/cic-vm /home/amoschen/workspace/cpp-cic/cic-vm/libcvm /home/amoschen/workspace/cpp-cic/cic-vm/libcvm/CMakeFiles/cvm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libcvm/CMakeFiles/cvm.dir/depend

