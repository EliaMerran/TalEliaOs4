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
include CMakeFiles/TalEliaOs4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TalEliaOs4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TalEliaOs4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TalEliaOs4.dir/flags.make

CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o: CMakeFiles/TalEliaOs4.dir/flags.make
CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o: ../PhysicalMemoryOriginal.cpp
CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o: CMakeFiles/TalEliaOs4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o -MF CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o.d -o CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o -c /cs/usr/suchetzky/os/ex4/PhysicalMemoryOriginal.cpp

CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/suchetzky/os/ex4/PhysicalMemoryOriginal.cpp > CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.i

CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/suchetzky/os/ex4/PhysicalMemoryOriginal.cpp -o CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.s

CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o: CMakeFiles/TalEliaOs4.dir/flags.make
CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o: ../SimpleTest.cpp
CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o: CMakeFiles/TalEliaOs4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o -MF CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o.d -o CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o -c /cs/usr/suchetzky/os/ex4/SimpleTest.cpp

CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/suchetzky/os/ex4/SimpleTest.cpp > CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.i

CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/suchetzky/os/ex4/SimpleTest.cpp -o CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.s

CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o: CMakeFiles/TalEliaOs4.dir/flags.make
CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o: ../VirtualMemory.cpp
CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o: CMakeFiles/TalEliaOs4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o -MF CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o.d -o CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o -c /cs/usr/suchetzky/os/ex4/VirtualMemory.cpp

CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/suchetzky/os/ex4/VirtualMemory.cpp > CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.i

CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/suchetzky/os/ex4/VirtualMemory.cpp -o CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.s

# Object files for target TalEliaOs4
TalEliaOs4_OBJECTS = \
"CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o" \
"CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o" \
"CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o"

# External object files for target TalEliaOs4
TalEliaOs4_EXTERNAL_OBJECTS =

TalEliaOs4: CMakeFiles/TalEliaOs4.dir/PhysicalMemoryOriginal.cpp.o
TalEliaOs4: CMakeFiles/TalEliaOs4.dir/SimpleTest.cpp.o
TalEliaOs4: CMakeFiles/TalEliaOs4.dir/VirtualMemory.cpp.o
TalEliaOs4: CMakeFiles/TalEliaOs4.dir/build.make
TalEliaOs4: CMakeFiles/TalEliaOs4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable TalEliaOs4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TalEliaOs4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TalEliaOs4.dir/build: TalEliaOs4
.PHONY : CMakeFiles/TalEliaOs4.dir/build

CMakeFiles/TalEliaOs4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TalEliaOs4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TalEliaOs4.dir/clean

CMakeFiles/TalEliaOs4.dir/depend:
	cd /cs/usr/suchetzky/os/ex4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cs/usr/suchetzky/os/ex4 /cs/usr/suchetzky/os/ex4 /cs/usr/suchetzky/os/ex4/cmake-build-debug /cs/usr/suchetzky/os/ex4/cmake-build-debug /cs/usr/suchetzky/os/ex4/cmake-build-debug/CMakeFiles/TalEliaOs4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TalEliaOs4.dir/depend
