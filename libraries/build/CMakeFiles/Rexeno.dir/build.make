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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hadrien/repos/newRexeno/libraries

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hadrien/repos/newRexeno/libraries/build

# Include any dependencies generated for this target.
include CMakeFiles/Rexeno.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Rexeno.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Rexeno.dir/flags.make

CMakeFiles/Rexeno.dir/main.cc.o: CMakeFiles/Rexeno.dir/flags.make
CMakeFiles/Rexeno.dir/main.cc.o: ../main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/hadrien/repos/newRexeno/libraries/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Rexeno.dir/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Rexeno.dir/main.cc.o -c /home/hadrien/repos/newRexeno/libraries/main.cc

CMakeFiles/Rexeno.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rexeno.dir/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/hadrien/repos/newRexeno/libraries/main.cc > CMakeFiles/Rexeno.dir/main.cc.i

CMakeFiles/Rexeno.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rexeno.dir/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/hadrien/repos/newRexeno/libraries/main.cc -o CMakeFiles/Rexeno.dir/main.cc.s

CMakeFiles/Rexeno.dir/main.cc.o.requires:
.PHONY : CMakeFiles/Rexeno.dir/main.cc.o.requires

CMakeFiles/Rexeno.dir/main.cc.o.provides: CMakeFiles/Rexeno.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/Rexeno.dir/build.make CMakeFiles/Rexeno.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/Rexeno.dir/main.cc.o.provides

CMakeFiles/Rexeno.dir/main.cc.o.provides.build: CMakeFiles/Rexeno.dir/main.cc.o

# Object files for target Rexeno
Rexeno_OBJECTS = \
"CMakeFiles/Rexeno.dir/main.cc.o"

# External object files for target Rexeno
Rexeno_EXTERNAL_OBJECTS =

Rexeno: CMakeFiles/Rexeno.dir/main.cc.o
Rexeno: configuration/libconfiguration.a
Rexeno: CMakeFiles/Rexeno.dir/build.make
Rexeno: CMakeFiles/Rexeno.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Rexeno"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Rexeno.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Rexeno.dir/build: Rexeno
.PHONY : CMakeFiles/Rexeno.dir/build

CMakeFiles/Rexeno.dir/requires: CMakeFiles/Rexeno.dir/main.cc.o.requires
.PHONY : CMakeFiles/Rexeno.dir/requires

CMakeFiles/Rexeno.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Rexeno.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Rexeno.dir/clean

CMakeFiles/Rexeno.dir/depend:
	cd /home/hadrien/repos/newRexeno/libraries/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hadrien/repos/newRexeno/libraries /home/hadrien/repos/newRexeno/libraries /home/hadrien/repos/newRexeno/libraries/build /home/hadrien/repos/newRexeno/libraries/build /home/hadrien/repos/newRexeno/libraries/build/CMakeFiles/Rexeno.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Rexeno.dir/depend

