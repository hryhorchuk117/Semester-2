# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/73/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/73/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hryhorchuk117/CLionProjects/chess_try2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/chess_try2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chess_try2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess_try2.dir/flags.make

CMakeFiles/chess_try2.dir/main.cpp.o: CMakeFiles/chess_try2.dir/flags.make
CMakeFiles/chess_try2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chess_try2.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess_try2.dir/main.cpp.o -c /home/hryhorchuk117/CLionProjects/chess_try2/main.cpp

CMakeFiles/chess_try2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess_try2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hryhorchuk117/CLionProjects/chess_try2/main.cpp > CMakeFiles/chess_try2.dir/main.cpp.i

CMakeFiles/chess_try2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess_try2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hryhorchuk117/CLionProjects/chess_try2/main.cpp -o CMakeFiles/chess_try2.dir/main.cpp.s

CMakeFiles/chess_try2.dir/figure.cpp.o: CMakeFiles/chess_try2.dir/flags.make
CMakeFiles/chess_try2.dir/figure.cpp.o: ../figure.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/chess_try2.dir/figure.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess_try2.dir/figure.cpp.o -c /home/hryhorchuk117/CLionProjects/chess_try2/figure.cpp

CMakeFiles/chess_try2.dir/figure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess_try2.dir/figure.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hryhorchuk117/CLionProjects/chess_try2/figure.cpp > CMakeFiles/chess_try2.dir/figure.cpp.i

CMakeFiles/chess_try2.dir/figure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess_try2.dir/figure.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hryhorchuk117/CLionProjects/chess_try2/figure.cpp -o CMakeFiles/chess_try2.dir/figure.cpp.s

CMakeFiles/chess_try2.dir/board.cpp.o: CMakeFiles/chess_try2.dir/flags.make
CMakeFiles/chess_try2.dir/board.cpp.o: ../board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/chess_try2.dir/board.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess_try2.dir/board.cpp.o -c /home/hryhorchuk117/CLionProjects/chess_try2/board.cpp

CMakeFiles/chess_try2.dir/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess_try2.dir/board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hryhorchuk117/CLionProjects/chess_try2/board.cpp > CMakeFiles/chess_try2.dir/board.cpp.i

CMakeFiles/chess_try2.dir/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess_try2.dir/board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hryhorchuk117/CLionProjects/chess_try2/board.cpp -o CMakeFiles/chess_try2.dir/board.cpp.s

CMakeFiles/chess_try2.dir/chess.cpp.o: CMakeFiles/chess_try2.dir/flags.make
CMakeFiles/chess_try2.dir/chess.cpp.o: ../chess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/chess_try2.dir/chess.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess_try2.dir/chess.cpp.o -c /home/hryhorchuk117/CLionProjects/chess_try2/chess.cpp

CMakeFiles/chess_try2.dir/chess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess_try2.dir/chess.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hryhorchuk117/CLionProjects/chess_try2/chess.cpp > CMakeFiles/chess_try2.dir/chess.cpp.i

CMakeFiles/chess_try2.dir/chess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess_try2.dir/chess.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hryhorchuk117/CLionProjects/chess_try2/chess.cpp -o CMakeFiles/chess_try2.dir/chess.cpp.s

# Object files for target chess_try2
chess_try2_OBJECTS = \
"CMakeFiles/chess_try2.dir/main.cpp.o" \
"CMakeFiles/chess_try2.dir/figure.cpp.o" \
"CMakeFiles/chess_try2.dir/board.cpp.o" \
"CMakeFiles/chess_try2.dir/chess.cpp.o"

# External object files for target chess_try2
chess_try2_EXTERNAL_OBJECTS =

chess_try2: CMakeFiles/chess_try2.dir/main.cpp.o
chess_try2: CMakeFiles/chess_try2.dir/figure.cpp.o
chess_try2: CMakeFiles/chess_try2.dir/board.cpp.o
chess_try2: CMakeFiles/chess_try2.dir/chess.cpp.o
chess_try2: CMakeFiles/chess_try2.dir/build.make
chess_try2: CMakeFiles/chess_try2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable chess_try2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chess_try2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess_try2.dir/build: chess_try2

.PHONY : CMakeFiles/chess_try2.dir/build

CMakeFiles/chess_try2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chess_try2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chess_try2.dir/clean

CMakeFiles/chess_try2.dir/depend:
	cd /home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hryhorchuk117/CLionProjects/chess_try2 /home/hryhorchuk117/CLionProjects/chess_try2 /home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug /home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug /home/hryhorchuk117/CLionProjects/chess_try2/cmake-build-debug/CMakeFiles/chess_try2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chess_try2.dir/depend
