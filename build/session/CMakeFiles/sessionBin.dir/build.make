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
CMAKE_BINARY_DIR = /home/xeno1/Desktop/rexeno/build

# Include any dependencies generated for this target.
include session/CMakeFiles/sessionBin.dir/depend.make

# Include the progress variables for this target.
include session/CMakeFiles/sessionBin.dir/progress.make

# Include the compile flags for this target's objects.
include session/CMakeFiles/sessionBin.dir/flags.make

session/CMakeFiles/sessionBin.dir/session.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/session.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/session.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/session.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/session.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/session.cc

session/CMakeFiles/sessionBin.dir/session.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/session.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/session.cc > CMakeFiles/sessionBin.dir/session.cc.i

session/CMakeFiles/sessionBin.dir/session.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/session.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/session.cc -o CMakeFiles/sessionBin.dir/session.cc.s

session/CMakeFiles/sessionBin.dir/session.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/session.cc.o.requires

session/CMakeFiles/sessionBin.dir/session.cc.o.provides: session/CMakeFiles/sessionBin.dir/session.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/session.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/session.cc.o.provides

session/CMakeFiles/sessionBin.dir/session.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/session.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/session.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/trial.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/trial.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/trial.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/trial.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/trial.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/trial.cc

session/CMakeFiles/sessionBin.dir/trial.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/trial.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/trial.cc > CMakeFiles/sessionBin.dir/trial.cc.i

session/CMakeFiles/sessionBin.dir/trial.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/trial.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/trial.cc -o CMakeFiles/sessionBin.dir/trial.cc.s

session/CMakeFiles/sessionBin.dir/trial.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/trial.cc.o.requires

session/CMakeFiles/sessionBin.dir/trial.cc.o.provides: session/CMakeFiles/sessionBin.dir/trial.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/trial.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/trial.cc.o.provides

session/CMakeFiles/sessionBin.dir/trial.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/trial.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/trial.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/shape.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/shape.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/shape.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/shape.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/shape.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/shape.cc

session/CMakeFiles/sessionBin.dir/shape.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/shape.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/shape.cc > CMakeFiles/sessionBin.dir/shape.cc.i

session/CMakeFiles/sessionBin.dir/shape.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/shape.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/shape.cc -o CMakeFiles/sessionBin.dir/shape.cc.s

session/CMakeFiles/sessionBin.dir/shape.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/shape.cc.o.requires

session/CMakeFiles/sessionBin.dir/shape.cc.o.provides: session/CMakeFiles/sessionBin.dir/shape.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/shape.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/shape.cc.o.provides

session/CMakeFiles/sessionBin.dir/shape.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/shape.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/shape.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/cross.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/cross.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/cross.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/cross.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/cross.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/cross.cc

session/CMakeFiles/sessionBin.dir/cross.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/cross.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/cross.cc > CMakeFiles/sessionBin.dir/cross.cc.i

session/CMakeFiles/sessionBin.dir/cross.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/cross.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/cross.cc -o CMakeFiles/sessionBin.dir/cross.cc.s

session/CMakeFiles/sessionBin.dir/cross.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/cross.cc.o.requires

session/CMakeFiles/sessionBin.dir/cross.cc.o.provides: session/CMakeFiles/sessionBin.dir/cross.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/cross.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/cross.cc.o.provides

session/CMakeFiles/sessionBin.dir/cross.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/cross.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/cross.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/square.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/square.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/square.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/square.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/square.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/square.cc

session/CMakeFiles/sessionBin.dir/square.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/square.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/square.cc > CMakeFiles/sessionBin.dir/square.cc.i

session/CMakeFiles/sessionBin.dir/square.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/square.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/square.cc -o CMakeFiles/sessionBin.dir/square.cc.s

session/CMakeFiles/sessionBin.dir/square.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/square.cc.o.requires

session/CMakeFiles/sessionBin.dir/square.cc.o.provides: session/CMakeFiles/sessionBin.dir/square.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/square.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/square.cc.o.provides

session/CMakeFiles/sessionBin.dir/square.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/square.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/square.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/rectangle.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/rectangle.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/rectangle.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/rectangle.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/rectangle.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/rectangle.cc

session/CMakeFiles/sessionBin.dir/rectangle.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/rectangle.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/rectangle.cc > CMakeFiles/sessionBin.dir/rectangle.cc.i

session/CMakeFiles/sessionBin.dir/rectangle.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/rectangle.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/rectangle.cc -o CMakeFiles/sessionBin.dir/rectangle.cc.s

session/CMakeFiles/sessionBin.dir/rectangle.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/rectangle.cc.o.requires

session/CMakeFiles/sessionBin.dir/rectangle.cc.o.provides: session/CMakeFiles/sessionBin.dir/rectangle.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/rectangle.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/rectangle.cc.o.provides

session/CMakeFiles/sessionBin.dir/rectangle.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/rectangle.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/rectangle.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/variable.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/variable.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/variable.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/variable.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/variable.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/variable.cc

session/CMakeFiles/sessionBin.dir/variable.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/variable.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/variable.cc > CMakeFiles/sessionBin.dir/variable.cc.i

session/CMakeFiles/sessionBin.dir/variable.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/variable.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/variable.cc -o CMakeFiles/sessionBin.dir/variable.cc.s

session/CMakeFiles/sessionBin.dir/variable.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/variable.cc.o.requires

session/CMakeFiles/sessionBin.dir/variable.cc.o.provides: session/CMakeFiles/sessionBin.dir/variable.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/variable.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/variable.cc.o.provides

session/CMakeFiles/sessionBin.dir/variable.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/variable.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/variable.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/setup.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/setup.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/setup.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/setup.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/setup.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/setup.cc

session/CMakeFiles/sessionBin.dir/setup.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/setup.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/setup.cc > CMakeFiles/sessionBin.dir/setup.cc.i

session/CMakeFiles/sessionBin.dir/setup.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/setup.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/setup.cc -o CMakeFiles/sessionBin.dir/setup.cc.s

session/CMakeFiles/sessionBin.dir/setup.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/setup.cc.o.requires

session/CMakeFiles/sessionBin.dir/setup.cc.o.provides: session/CMakeFiles/sessionBin.dir/setup.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/setup.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/setup.cc.o.provides

session/CMakeFiles/sessionBin.dir/setup.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/setup.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/setup.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/window.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/window.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/window.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/window.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/window.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/window.cc

session/CMakeFiles/sessionBin.dir/window.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/window.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/window.cc > CMakeFiles/sessionBin.dir/window.cc.i

session/CMakeFiles/sessionBin.dir/window.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/window.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/window.cc -o CMakeFiles/sessionBin.dir/window.cc.s

session/CMakeFiles/sessionBin.dir/window.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/window.cc.o.requires

session/CMakeFiles/sessionBin.dir/window.cc.o.provides: session/CMakeFiles/sessionBin.dir/window.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/window.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/window.cc.o.provides

session/CMakeFiles/sessionBin.dir/window.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/window.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/window.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/mainSession.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/mainSession.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/mainSession.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/mainSession.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/mainSession.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/mainSession.cc

session/CMakeFiles/sessionBin.dir/mainSession.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/mainSession.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/mainSession.cc > CMakeFiles/sessionBin.dir/mainSession.cc.i

session/CMakeFiles/sessionBin.dir/mainSession.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/mainSession.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/mainSession.cc -o CMakeFiles/sessionBin.dir/mainSession.cc.s

session/CMakeFiles/sessionBin.dir/mainSession.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/mainSession.cc.o.requires

session/CMakeFiles/sessionBin.dir/mainSession.cc.o.provides: session/CMakeFiles/sessionBin.dir/mainSession.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/mainSession.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/mainSession.cc.o.provides

session/CMakeFiles/sessionBin.dir/mainSession.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/mainSession.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/mainSession.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/sphere.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/sphere.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/sphere.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/sphere.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/sphere.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/sphere.cc

session/CMakeFiles/sessionBin.dir/sphere.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/sphere.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/sphere.cc > CMakeFiles/sessionBin.dir/sphere.cc.i

session/CMakeFiles/sessionBin.dir/sphere.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/sphere.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/sphere.cc -o CMakeFiles/sessionBin.dir/sphere.cc.s

session/CMakeFiles/sessionBin.dir/sphere.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/sphere.cc.o.requires

session/CMakeFiles/sessionBin.dir/sphere.cc.o.provides: session/CMakeFiles/sessionBin.dir/sphere.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/sphere.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/sphere.cc.o.provides

session/CMakeFiles/sessionBin.dir/sphere.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/sphere.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/sphere.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/plan.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/plan.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/plan.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/plan.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/plan.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/plan.cc

session/CMakeFiles/sessionBin.dir/plan.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/plan.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/plan.cc > CMakeFiles/sessionBin.dir/plan.cc.i

session/CMakeFiles/sessionBin.dir/plan.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/plan.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/plan.cc -o CMakeFiles/sessionBin.dir/plan.cc.s

session/CMakeFiles/sessionBin.dir/plan.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/plan.cc.o.requires

session/CMakeFiles/sessionBin.dir/plan.cc.o.provides: session/CMakeFiles/sessionBin.dir/plan.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/plan.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/plan.cc.o.provides

session/CMakeFiles/sessionBin.dir/plan.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/plan.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/plan.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/imageload.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/imageload.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/imageload.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/imageload.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/imageload.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/imageload.cc

session/CMakeFiles/sessionBin.dir/imageload.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/imageload.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/imageload.cc > CMakeFiles/sessionBin.dir/imageload.cc.i

session/CMakeFiles/sessionBin.dir/imageload.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/imageload.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/imageload.cc -o CMakeFiles/sessionBin.dir/imageload.cc.s

session/CMakeFiles/sessionBin.dir/imageload.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/imageload.cc.o.requires

session/CMakeFiles/sessionBin.dir/imageload.cc.o.provides: session/CMakeFiles/sessionBin.dir/imageload.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/imageload.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/imageload.cc.o.provides

session/CMakeFiles/sessionBin.dir/imageload.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/imageload.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/imageload.cc.o.provides.build

session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o: session/CMakeFiles/sessionBin.dir/flags.make
session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o: /home/xeno1/Desktop/rexeno/libraries/session/sphereshadow.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xeno1/Desktop/rexeno/build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sessionBin.dir/sphereshadow.cc.o -c /home/xeno1/Desktop/rexeno/libraries/session/sphereshadow.cc

session/CMakeFiles/sessionBin.dir/sphereshadow.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sessionBin.dir/sphereshadow.cc.i"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xeno1/Desktop/rexeno/libraries/session/sphereshadow.cc > CMakeFiles/sessionBin.dir/sphereshadow.cc.i

session/CMakeFiles/sessionBin.dir/sphereshadow.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sessionBin.dir/sphereshadow.cc.s"
	cd /home/xeno1/Desktop/rexeno/build/session && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xeno1/Desktop/rexeno/libraries/session/sphereshadow.cc -o CMakeFiles/sessionBin.dir/sphereshadow.cc.s

session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.requires:
.PHONY : session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.requires

session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.provides: session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.requires
	$(MAKE) -f session/CMakeFiles/sessionBin.dir/build.make session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.provides.build
.PHONY : session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.provides

session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.provides.build: session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o
.PHONY : session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.provides.build

# Object files for target sessionBin
sessionBin_OBJECTS = \
"CMakeFiles/sessionBin.dir/session.cc.o" \
"CMakeFiles/sessionBin.dir/trial.cc.o" \
"CMakeFiles/sessionBin.dir/shape.cc.o" \
"CMakeFiles/sessionBin.dir/cross.cc.o" \
"CMakeFiles/sessionBin.dir/square.cc.o" \
"CMakeFiles/sessionBin.dir/rectangle.cc.o" \
"CMakeFiles/sessionBin.dir/variable.cc.o" \
"CMakeFiles/sessionBin.dir/setup.cc.o" \
"CMakeFiles/sessionBin.dir/window.cc.o" \
"CMakeFiles/sessionBin.dir/mainSession.cc.o" \
"CMakeFiles/sessionBin.dir/sphere.cc.o" \
"CMakeFiles/sessionBin.dir/plan.cc.o" \
"CMakeFiles/sessionBin.dir/imageload.cc.o" \
"CMakeFiles/sessionBin.dir/sphereshadow.cc.o"

# External object files for target sessionBin
sessionBin_EXTERNAL_OBJECTS =

session/sessionBin: session/CMakeFiles/sessionBin.dir/session.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/trial.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/shape.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/cross.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/square.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/rectangle.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/variable.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/setup.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/window.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/mainSession.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/sphere.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/plan.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/imageload.cc.o
session/sessionBin: session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o
session/sessionBin: configuration/libconfiguration.so
session/sessionBin: driver/libdriver.so
session/sessionBin: recorder/librecorder.so
session/sessionBin: session/CMakeFiles/sessionBin.dir/build.make
session/sessionBin: session/CMakeFiles/sessionBin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sessionBin"
	cd /home/xeno1/Desktop/rexeno/build/session && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sessionBin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
session/CMakeFiles/sessionBin.dir/build: session/sessionBin
.PHONY : session/CMakeFiles/sessionBin.dir/build

session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/session.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/trial.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/shape.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/cross.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/square.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/rectangle.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/variable.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/setup.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/window.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/mainSession.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/sphere.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/plan.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/imageload.cc.o.requires
session/CMakeFiles/sessionBin.dir/requires: session/CMakeFiles/sessionBin.dir/sphereshadow.cc.o.requires
.PHONY : session/CMakeFiles/sessionBin.dir/requires

session/CMakeFiles/sessionBin.dir/clean:
	cd /home/xeno1/Desktop/rexeno/build/session && $(CMAKE_COMMAND) -P CMakeFiles/sessionBin.dir/cmake_clean.cmake
.PHONY : session/CMakeFiles/sessionBin.dir/clean

session/CMakeFiles/sessionBin.dir/depend:
	cd /home/xeno1/Desktop/rexeno/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xeno1/Desktop/rexeno/libraries /home/xeno1/Desktop/rexeno/libraries/session /home/xeno1/Desktop/rexeno/build /home/xeno1/Desktop/rexeno/build/session /home/xeno1/Desktop/rexeno/build/session/CMakeFiles/sessionBin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : session/CMakeFiles/sessionBin.dir/depend

