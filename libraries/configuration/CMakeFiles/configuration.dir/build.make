# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_SOURCE_DIR = /home/xeno1/Desktop/rexeno/libraries

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xeno1/Desktop/rexeno/libraries

# Include any dependencies generated for this target.
include configuration/CMakeFiles/configuration.dir/depend.make

# Include the progress variables for this target.
include configuration/CMakeFiles/configuration.dir/progress.make

# Include the compile flags for this target's objects.
include configuration/CMakeFiles/configuration.dir/flags.make

configuration/CMakeFiles/configuration.dir/parser.cc.o: configuration/CMakeFiles/configuration.dir/flags.make
configuration/CMakeFiles/configuration.dir/parser.cc.o: configuration/parser.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/libraries/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object configuration/CMakeFiles/configuration.dir/parser.cc.o"
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/configuration.dir/parser.cc.o -c /home/xeno1/Desktop/rexeno/libraries/configuration/parser.cc

configuration/CMakeFiles/configuration.dir/parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/configuration.dir/parser.cc.i"
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/configuration/parser.cc > CMakeFiles/configuration.dir/parser.cc.i

configuration/CMakeFiles/configuration.dir/parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/configuration.dir/parser.cc.s"
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/configuration/parser.cc -o CMakeFiles/configuration.dir/parser.cc.s

configuration/CMakeFiles/configuration.dir/parser.cc.o.requires:
.PHONY : configuration/CMakeFiles/configuration.dir/parser.cc.o.requires

configuration/CMakeFiles/configuration.dir/parser.cc.o.provides: configuration/CMakeFiles/configuration.dir/parser.cc.o.requires
	$(MAKE) -f configuration/CMakeFiles/configuration.dir/build.make configuration/CMakeFiles/configuration.dir/parser.cc.o.provides.build
.PHONY : configuration/CMakeFiles/configuration.dir/parser.cc.o.provides

configuration/CMakeFiles/configuration.dir/parser.cc.o.provides.build: configuration/CMakeFiles/configuration.dir/parser.cc.o
.PHONY : configuration/CMakeFiles/configuration.dir/parser.cc.o.provides.build

configuration/CMakeFiles/configuration.dir/order_parser.cc.o: configuration/CMakeFiles/configuration.dir/flags.make
configuration/CMakeFiles/configuration.dir/order_parser.cc.o: configuration/order_parser.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/libraries/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object configuration/CMakeFiles/configuration.dir/order_parser.cc.o"
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/configuration.dir/order_parser.cc.o -c /home/xeno1/Desktop/rexeno/libraries/configuration/order_parser.cc

configuration/CMakeFiles/configuration.dir/order_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/configuration.dir/order_parser.cc.i"
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/configuration/order_parser.cc > CMakeFiles/configuration.dir/order_parser.cc.i

configuration/CMakeFiles/configuration.dir/order_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/configuration.dir/order_parser.cc.s"
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/configuration/order_parser.cc -o CMakeFiles/configuration.dir/order_parser.cc.s

configuration/CMakeFiles/configuration.dir/order_parser.cc.o.requires:
.PHONY : configuration/CMakeFiles/configuration.dir/order_parser.cc.o.requires

configuration/CMakeFiles/configuration.dir/order_parser.cc.o.provides: configuration/CMakeFiles/configuration.dir/order_parser.cc.o.requires
	$(MAKE) -f configuration/CMakeFiles/configuration.dir/build.make configuration/CMakeFiles/configuration.dir/order_parser.cc.o.provides.build
.PHONY : configuration/CMakeFiles/configuration.dir/order_parser.cc.o.provides

configuration/CMakeFiles/configuration.dir/order_parser.cc.o.provides.build: configuration/CMakeFiles/configuration.dir/order_parser.cc.o
.PHONY : configuration/CMakeFiles/configuration.dir/order_parser.cc.o.provides.build

# Object files for target configuration
configuration_OBJECTS = \
"CMakeFiles/configuration.dir/parser.cc.o" \
"CMakeFiles/configuration.dir/order_parser.cc.o"

# External object files for target configuration
configuration_EXTERNAL_OBJECTS =

configuration/libconfiguration.so: configuration/CMakeFiles/configuration.dir/parser.cc.o
configuration/libconfiguration.so: configuration/CMakeFiles/configuration.dir/order_parser.cc.o
configuration/libconfiguration.so: configuration/CMakeFiles/configuration.dir/build.make
configuration/libconfiguration.so: configuration/CMakeFiles/configuration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libconfiguration.so"
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/configuration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
configuration/CMakeFiles/configuration.dir/build: configuration/libconfiguration.so
.PHONY : configuration/CMakeFiles/configuration.dir/build

configuration/CMakeFiles/configuration.dir/requires: configuration/CMakeFiles/configuration.dir/parser.cc.o.requires
configuration/CMakeFiles/configuration.dir/requires: configuration/CMakeFiles/configuration.dir/order_parser.cc.o.requires
.PHONY : configuration/CMakeFiles/configuration.dir/requires

configuration/CMakeFiles/configuration.dir/clean:
	cd /home/xeno1/Desktop/rexeno/libraries/configuration && $(CMAKE_COMMAND) -P CMakeFiles/configuration.dir/cmake_clean.cmake
.PHONY : configuration/CMakeFiles/configuration.dir/clean

configuration/CMakeFiles/configuration.dir/depend:
	cd /home/xeno1/Desktop/rexeno/libraries && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xeno1/Desktop/rexeno/libraries /home/xeno1/Desktop/rexeno/libraries/configuration /home/xeno1/Desktop/rexeno/libraries /home/xeno1/Desktop/rexeno/libraries/configuration /home/xeno1/Desktop/rexeno/libraries/configuration/CMakeFiles/configuration.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : configuration/CMakeFiles/configuration.dir/depend

