# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pramos/Documents/Univ/SETR_Proj2/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pramos/Documents/Univ/SETR_Proj2/src/build

# Include any dependencies generated for this target.
include modules/CMakeFiles/cmdproc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include modules/CMakeFiles/cmdproc.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/CMakeFiles/cmdproc.dir/progress.make

# Include the compile flags for this target's objects.
include modules/CMakeFiles/cmdproc.dir/flags.make

modules/CMakeFiles/cmdproc.dir/codegen:
.PHONY : modules/CMakeFiles/cmdproc.dir/codegen

modules/CMakeFiles/cmdproc.dir/cmdproc.c.o: modules/CMakeFiles/cmdproc.dir/flags.make
modules/CMakeFiles/cmdproc.dir/cmdproc.c.o: /home/pramos/Documents/Univ/SETR_Proj2/src/modules/cmdproc.c
modules/CMakeFiles/cmdproc.dir/cmdproc.c.o: modules/CMakeFiles/cmdproc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/pramos/Documents/Univ/SETR_Proj2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object modules/CMakeFiles/cmdproc.dir/cmdproc.c.o"
	cd /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/CMakeFiles/cmdproc.dir/cmdproc.c.o -MF CMakeFiles/cmdproc.dir/cmdproc.c.o.d -o CMakeFiles/cmdproc.dir/cmdproc.c.o -c /home/pramos/Documents/Univ/SETR_Proj2/src/modules/cmdproc.c

modules/CMakeFiles/cmdproc.dir/cmdproc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cmdproc.dir/cmdproc.c.i"
	cd /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pramos/Documents/Univ/SETR_Proj2/src/modules/cmdproc.c > CMakeFiles/cmdproc.dir/cmdproc.c.i

modules/CMakeFiles/cmdproc.dir/cmdproc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cmdproc.dir/cmdproc.c.s"
	cd /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pramos/Documents/Univ/SETR_Proj2/src/modules/cmdproc.c -o CMakeFiles/cmdproc.dir/cmdproc.c.s

# Object files for target cmdproc
cmdproc_OBJECTS = \
"CMakeFiles/cmdproc.dir/cmdproc.c.o"

# External object files for target cmdproc
cmdproc_EXTERNAL_OBJECTS =

modules/libcmdproc.a: modules/CMakeFiles/cmdproc.dir/cmdproc.c.o
modules/libcmdproc.a: modules/CMakeFiles/cmdproc.dir/build.make
modules/libcmdproc.a: modules/CMakeFiles/cmdproc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/pramos/Documents/Univ/SETR_Proj2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libcmdproc.a"
	cd /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/cmdproc.dir/cmake_clean_target.cmake
	cd /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmdproc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/CMakeFiles/cmdproc.dir/build: modules/libcmdproc.a
.PHONY : modules/CMakeFiles/cmdproc.dir/build

modules/CMakeFiles/cmdproc.dir/clean:
	cd /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/cmdproc.dir/cmake_clean.cmake
.PHONY : modules/CMakeFiles/cmdproc.dir/clean

modules/CMakeFiles/cmdproc.dir/depend:
	cd /home/pramos/Documents/Univ/SETR_Proj2/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pramos/Documents/Univ/SETR_Proj2/src /home/pramos/Documents/Univ/SETR_Proj2/src/modules /home/pramos/Documents/Univ/SETR_Proj2/src/build /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules /home/pramos/Documents/Univ/SETR_Proj2/src/build/modules/CMakeFiles/cmdproc.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : modules/CMakeFiles/cmdproc.dir/depend

