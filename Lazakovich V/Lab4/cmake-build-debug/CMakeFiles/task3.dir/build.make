# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\GitHub\Laboratory-works\Lazakovich V\Lab4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\GitHub\Laboratory-works\Lazakovich V\Lab4\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/task3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/task3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/task3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task3.dir/flags.make

CMakeFiles/task3.dir/4_3.c.obj: CMakeFiles/task3.dir/flags.make
CMakeFiles/task3.dir/4_3.c.obj: ../4_3.c
CMakeFiles/task3.dir/4_3.c.obj: CMakeFiles/task3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\GitHub\Laboratory-works\Lazakovich V\Lab4\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task3.dir/4_3.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/task3.dir/4_3.c.obj -MF CMakeFiles\task3.dir\4_3.c.obj.d -o CMakeFiles\task3.dir\4_3.c.obj -c "C:\GitHub\Laboratory-works\Lazakovich V\Lab4\4_3.c"

CMakeFiles/task3.dir/4_3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task3.dir/4_3.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\GitHub\Laboratory-works\Lazakovich V\Lab4\4_3.c" > CMakeFiles\task3.dir\4_3.c.i

CMakeFiles/task3.dir/4_3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task3.dir/4_3.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\GitHub\Laboratory-works\Lazakovich V\Lab4\4_3.c" -o CMakeFiles\task3.dir\4_3.c.s

# Object files for target task3
task3_OBJECTS = \
"CMakeFiles/task3.dir/4_3.c.obj"

# External object files for target task3
task3_EXTERNAL_OBJECTS =

task3.exe: CMakeFiles/task3.dir/4_3.c.obj
task3.exe: CMakeFiles/task3.dir/build.make
task3.exe: CMakeFiles/task3.dir/linklibs.rsp
task3.exe: CMakeFiles/task3.dir/objects1.rsp
task3.exe: CMakeFiles/task3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\GitHub\Laboratory-works\Lazakovich V\Lab4\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable task3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\task3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task3.dir/build: task3.exe
.PHONY : CMakeFiles/task3.dir/build

CMakeFiles/task3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\task3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/task3.dir/clean

CMakeFiles/task3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\GitHub\Laboratory-works\Lazakovich V\Lab4" "C:\GitHub\Laboratory-works\Lazakovich V\Lab4" "C:\GitHub\Laboratory-works\Lazakovich V\Lab4\cmake-build-debug" "C:\GitHub\Laboratory-works\Lazakovich V\Lab4\cmake-build-debug" "C:\GitHub\Laboratory-works\Lazakovich V\Lab4\cmake-build-debug\CMakeFiles\task3.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/task3.dir/depend

