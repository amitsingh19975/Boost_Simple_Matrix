# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Amit/Desktop/Python/c++/boost

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Amit/Desktop/Python/c++/boost

# Include any dependencies generated for this target.
include CMakeFiles/Simple_Matrix.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Simple_Matrix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Simple_Matrix.dir/flags.make

CMakeFiles/Simple_Matrix.dir/main.cpp.o: CMakeFiles/Simple_Matrix.dir/flags.make
CMakeFiles/Simple_Matrix.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Amit/Desktop/Python/c++/boost/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Simple_Matrix.dir/main.cpp.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/local/Cellar/llvm/6.0.1/bin/clang-tidy;-checks=*" --source=/Users/Amit/Desktop/Python/c++/boost/main.cpp -- /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Simple_Matrix.dir/main.cpp.o -c /Users/Amit/Desktop/Python/c++/boost/main.cpp

CMakeFiles/Simple_Matrix.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Simple_Matrix.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Amit/Desktop/Python/c++/boost/main.cpp > CMakeFiles/Simple_Matrix.dir/main.cpp.i

CMakeFiles/Simple_Matrix.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Simple_Matrix.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Amit/Desktop/Python/c++/boost/main.cpp -o CMakeFiles/Simple_Matrix.dir/main.cpp.s

# Object files for target Simple_Matrix
Simple_Matrix_OBJECTS = \
"CMakeFiles/Simple_Matrix.dir/main.cpp.o"

# External object files for target Simple_Matrix
Simple_Matrix_EXTERNAL_OBJECTS =

bin/Simple_Matrix: CMakeFiles/Simple_Matrix.dir/main.cpp.o
bin/Simple_Matrix: CMakeFiles/Simple_Matrix.dir/build.make
bin/Simple_Matrix: CMakeFiles/Simple_Matrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Amit/Desktop/Python/c++/boost/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/Simple_Matrix"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Simple_Matrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Simple_Matrix.dir/build: bin/Simple_Matrix

.PHONY : CMakeFiles/Simple_Matrix.dir/build

CMakeFiles/Simple_Matrix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Simple_Matrix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Simple_Matrix.dir/clean

CMakeFiles/Simple_Matrix.dir/depend:
	cd /Users/Amit/Desktop/Python/c++/boost && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Amit/Desktop/Python/c++/boost /Users/Amit/Desktop/Python/c++/boost /Users/Amit/Desktop/Python/c++/boost /Users/Amit/Desktop/Python/c++/boost /Users/Amit/Desktop/Python/c++/boost/CMakeFiles/Simple_Matrix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Simple_Matrix.dir/depend

