# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/Ohjelmointi/TeaNES

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/Ohjelmointi/TeaNES

# Include any dependencies generated for this target.
include CMakeFiles/TeaNES.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TeaNES.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TeaNES.dir/flags.make

CMakeFiles/TeaNES.dir/TeaNES.cpp.o: CMakeFiles/TeaNES.dir/flags.make
CMakeFiles/TeaNES.dir/TeaNES.cpp.o: TeaNES.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/e/Ohjelmointi/TeaNES/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/TeaNES.dir/TeaNES.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TeaNES.dir/TeaNES.cpp.o -c /mnt/e/Ohjelmointi/TeaNES/TeaNES.cpp

CMakeFiles/TeaNES.dir/TeaNES.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TeaNES.dir/TeaNES.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/e/Ohjelmointi/TeaNES/TeaNES.cpp > CMakeFiles/TeaNES.dir/TeaNES.cpp.i

CMakeFiles/TeaNES.dir/TeaNES.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TeaNES.dir/TeaNES.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/e/Ohjelmointi/TeaNES/TeaNES.cpp -o CMakeFiles/TeaNES.dir/TeaNES.cpp.s

CMakeFiles/TeaNES.dir/TeaNES.cpp.o.requires:
.PHONY : CMakeFiles/TeaNES.dir/TeaNES.cpp.o.requires

CMakeFiles/TeaNES.dir/TeaNES.cpp.o.provides: CMakeFiles/TeaNES.dir/TeaNES.cpp.o.requires
	$(MAKE) -f CMakeFiles/TeaNES.dir/build.make CMakeFiles/TeaNES.dir/TeaNES.cpp.o.provides.build
.PHONY : CMakeFiles/TeaNES.dir/TeaNES.cpp.o.provides

CMakeFiles/TeaNES.dir/TeaNES.cpp.o.provides.build: CMakeFiles/TeaNES.dir/TeaNES.cpp.o

# Object files for target TeaNES
TeaNES_OBJECTS = \
"CMakeFiles/TeaNES.dir/TeaNES.cpp.o"

# External object files for target TeaNES
TeaNES_EXTERNAL_OBJECTS =

TeaNES: CMakeFiles/TeaNES.dir/TeaNES.cpp.o
TeaNES: CMakeFiles/TeaNES.dir/build.make
TeaNES: CMakeFiles/TeaNES.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable TeaNES"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TeaNES.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TeaNES.dir/build: TeaNES
.PHONY : CMakeFiles/TeaNES.dir/build

CMakeFiles/TeaNES.dir/requires: CMakeFiles/TeaNES.dir/TeaNES.cpp.o.requires
.PHONY : CMakeFiles/TeaNES.dir/requires

CMakeFiles/TeaNES.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TeaNES.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TeaNES.dir/clean

CMakeFiles/TeaNES.dir/depend:
	cd /mnt/e/Ohjelmointi/TeaNES && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/Ohjelmointi/TeaNES /mnt/e/Ohjelmointi/TeaNES /mnt/e/Ohjelmointi/TeaNES /mnt/e/Ohjelmointi/TeaNES /mnt/e/Ohjelmointi/TeaNES/CMakeFiles/TeaNES.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TeaNES.dir/depend

