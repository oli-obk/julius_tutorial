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
CMAKE_SOURCE_DIR = /home/julius/julius_tutorial/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/julius/julius_tutorial/test

# Include any dependencies generated for this target.
include CMakeFiles/Example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Example.dir/flags.make

CMakeFiles/Example.dir/main.cpp.o: CMakeFiles/Example.dir/flags.make
CMakeFiles/Example.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/julius/julius_tutorial/test/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Example.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Example.dir/main.cpp.o -c /home/julius/julius_tutorial/test/main.cpp

CMakeFiles/Example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Example.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/julius/julius_tutorial/test/main.cpp > CMakeFiles/Example.dir/main.cpp.i

CMakeFiles/Example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Example.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/julius/julius_tutorial/test/main.cpp -o CMakeFiles/Example.dir/main.cpp.s

CMakeFiles/Example.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/Example.dir/main.cpp.o.requires

CMakeFiles/Example.dir/main.cpp.o.provides: CMakeFiles/Example.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Example.dir/build.make CMakeFiles/Example.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Example.dir/main.cpp.o.provides

CMakeFiles/Example.dir/main.cpp.o.provides.build: CMakeFiles/Example.dir/main.cpp.o

CMakeFiles/Example.dir/fun.cpp.o: CMakeFiles/Example.dir/flags.make
CMakeFiles/Example.dir/fun.cpp.o: fun.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/julius/julius_tutorial/test/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Example.dir/fun.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Example.dir/fun.cpp.o -c /home/julius/julius_tutorial/test/fun.cpp

CMakeFiles/Example.dir/fun.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Example.dir/fun.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/julius/julius_tutorial/test/fun.cpp > CMakeFiles/Example.dir/fun.cpp.i

CMakeFiles/Example.dir/fun.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Example.dir/fun.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/julius/julius_tutorial/test/fun.cpp -o CMakeFiles/Example.dir/fun.cpp.s

CMakeFiles/Example.dir/fun.cpp.o.requires:
.PHONY : CMakeFiles/Example.dir/fun.cpp.o.requires

CMakeFiles/Example.dir/fun.cpp.o.provides: CMakeFiles/Example.dir/fun.cpp.o.requires
	$(MAKE) -f CMakeFiles/Example.dir/build.make CMakeFiles/Example.dir/fun.cpp.o.provides.build
.PHONY : CMakeFiles/Example.dir/fun.cpp.o.provides

CMakeFiles/Example.dir/fun.cpp.o.provides.build: CMakeFiles/Example.dir/fun.cpp.o

# Object files for target Example
Example_OBJECTS = \
"CMakeFiles/Example.dir/main.cpp.o" \
"CMakeFiles/Example.dir/fun.cpp.o"

# External object files for target Example
Example_EXTERNAL_OBJECTS =

Example: CMakeFiles/Example.dir/main.cpp.o
Example: CMakeFiles/Example.dir/fun.cpp.o
Example: CMakeFiles/Example.dir/build.make
Example: CMakeFiles/Example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Example.dir/build: Example
.PHONY : CMakeFiles/Example.dir/build

CMakeFiles/Example.dir/requires: CMakeFiles/Example.dir/main.cpp.o.requires
CMakeFiles/Example.dir/requires: CMakeFiles/Example.dir/fun.cpp.o.requires
.PHONY : CMakeFiles/Example.dir/requires

CMakeFiles/Example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Example.dir/clean

CMakeFiles/Example.dir/depend:
	cd /home/julius/julius_tutorial/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julius/julius_tutorial/test /home/julius/julius_tutorial/test /home/julius/julius_tutorial/test /home/julius/julius_tutorial/test /home/julius/julius_tutorial/test/CMakeFiles/Example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Example.dir/depend

