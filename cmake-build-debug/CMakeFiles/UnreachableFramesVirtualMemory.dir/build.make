# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/APP/jetbrains/clion/2022.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/local/APP/jetbrains/clion/2022.1.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cs/usr/suchetzky/os/ex4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cs/usr/suchetzky/os/ex4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/UnreachableFramesVirtualMemory.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/UnreachableFramesVirtualMemory.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/UnreachableFramesVirtualMemory.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UnreachableFramesVirtualMemory.dir/flags.make

CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o: CMakeFiles/UnreachableFramesVirtualMemory.dir/flags.make
CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o: ../VirtualMemory.cpp
CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o: CMakeFiles/UnreachableFramesVirtualMemory.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o -MF CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o.d -o CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o -c /cs/usr/suchetzky/os/ex4/VirtualMemory.cpp

CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/suchetzky/os/ex4/VirtualMemory.cpp > CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.i

CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/suchetzky/os/ex4/VirtualMemory.cpp -o CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.s

CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o: CMakeFiles/UnreachableFramesVirtualMemory.dir/flags.make
CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o: ../PhysicalMemory.cpp
CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o: CMakeFiles/UnreachableFramesVirtualMemory.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o -MF CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o.d -o CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o -c /cs/usr/suchetzky/os/ex4/PhysicalMemory.cpp

CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/suchetzky/os/ex4/PhysicalMemory.cpp > CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.i

CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/suchetzky/os/ex4/PhysicalMemory.cpp -o CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.s

# Object files for target UnreachableFramesVirtualMemory
UnreachableFramesVirtualMemory_OBJECTS = \
"CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o" \
"CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o"

# External object files for target UnreachableFramesVirtualMemory
UnreachableFramesVirtualMemory_EXTERNAL_OBJECTS =

libUnreachableFramesVirtualMemory.a: CMakeFiles/UnreachableFramesVirtualMemory.dir/VirtualMemory.cpp.o
libUnreachableFramesVirtualMemory.a: CMakeFiles/UnreachableFramesVirtualMemory.dir/PhysicalMemory.cpp.o
libUnreachableFramesVirtualMemory.a: CMakeFiles/UnreachableFramesVirtualMemory.dir/build.make
libUnreachableFramesVirtualMemory.a: CMakeFiles/UnreachableFramesVirtualMemory.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libUnreachableFramesVirtualMemory.a"
	$(CMAKE_COMMAND) -P CMakeFiles/UnreachableFramesVirtualMemory.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UnreachableFramesVirtualMemory.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UnreachableFramesVirtualMemory.dir/build: libUnreachableFramesVirtualMemory.a
.PHONY : CMakeFiles/UnreachableFramesVirtualMemory.dir/build

CMakeFiles/UnreachableFramesVirtualMemory.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UnreachableFramesVirtualMemory.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UnreachableFramesVirtualMemory.dir/clean

CMakeFiles/UnreachableFramesVirtualMemory.dir/depend:
	cd /cs/usr/suchetzky/os/ex4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cs/usr/suchetzky/os/ex4 /cs/usr/suchetzky/os/ex4 /cs/usr/suchetzky/os/ex4/cmake-build-debug /cs/usr/suchetzky/os/ex4/cmake-build-debug /cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles/UnreachableFramesVirtualMemory.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UnreachableFramesVirtualMemory.dir/depend

