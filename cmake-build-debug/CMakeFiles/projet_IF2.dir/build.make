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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\fanig\Documents\GitHub\projet_IF2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\fanig\Documents\GitHub\projet_IF2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/projet_IF2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/projet_IF2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/projet_IF2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/projet_IF2.dir/flags.make

CMakeFiles/projet_IF2.dir/src/main.c.obj: CMakeFiles/projet_IF2.dir/flags.make
CMakeFiles/projet_IF2.dir/src/main.c.obj: CMakeFiles/projet_IF2.dir/includes_C.rsp
CMakeFiles/projet_IF2.dir/src/main.c.obj: ../src/main.c
CMakeFiles/projet_IF2.dir/src/main.c.obj: CMakeFiles/projet_IF2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\fanig\Documents\GitHub\projet_IF2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/projet_IF2.dir/src/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projet_IF2.dir/src/main.c.obj -MF CMakeFiles\projet_IF2.dir\src\main.c.obj.d -o CMakeFiles\projet_IF2.dir\src\main.c.obj -c C:\Users\fanig\Documents\GitHub\projet_IF2\src\main.c

CMakeFiles/projet_IF2.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet_IF2.dir/src/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\fanig\Documents\GitHub\projet_IF2\src\main.c > CMakeFiles\projet_IF2.dir\src\main.c.i

CMakeFiles/projet_IF2.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet_IF2.dir/src/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\fanig\Documents\GitHub\projet_IF2\src\main.c -o CMakeFiles\projet_IF2.dir\src\main.c.s

CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj: CMakeFiles/projet_IF2.dir/flags.make
CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj: CMakeFiles/projet_IF2.dir/includes_C.rsp
CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj: ../src/init_Plateau.c
CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj: CMakeFiles/projet_IF2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\fanig\Documents\GitHub\projet_IF2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj -MF CMakeFiles\projet_IF2.dir\src\init_Plateau.c.obj.d -o CMakeFiles\projet_IF2.dir\src\init_Plateau.c.obj -c C:\Users\fanig\Documents\GitHub\projet_IF2\src\init_Plateau.c

CMakeFiles/projet_IF2.dir/src/init_Plateau.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet_IF2.dir/src/init_Plateau.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\fanig\Documents\GitHub\projet_IF2\src\init_Plateau.c > CMakeFiles\projet_IF2.dir\src\init_Plateau.c.i

CMakeFiles/projet_IF2.dir/src/init_Plateau.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet_IF2.dir/src/init_Plateau.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\fanig\Documents\GitHub\projet_IF2\src\init_Plateau.c -o CMakeFiles\projet_IF2.dir\src\init_Plateau.c.s

# Object files for target projet_IF2
projet_IF2_OBJECTS = \
"CMakeFiles/projet_IF2.dir/src/main.c.obj" \
"CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj"

# External object files for target projet_IF2
projet_IF2_EXTERNAL_OBJECTS =

projet_IF2.exe: CMakeFiles/projet_IF2.dir/src/main.c.obj
projet_IF2.exe: CMakeFiles/projet_IF2.dir/src/init_Plateau.c.obj
projet_IF2.exe: CMakeFiles/projet_IF2.dir/build.make
projet_IF2.exe: CMakeFiles/projet_IF2.dir/linklibs.rsp
projet_IF2.exe: CMakeFiles/projet_IF2.dir/objects1.rsp
projet_IF2.exe: CMakeFiles/projet_IF2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\fanig\Documents\GitHub\projet_IF2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable projet_IF2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\projet_IF2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/projet_IF2.dir/build: projet_IF2.exe
.PHONY : CMakeFiles/projet_IF2.dir/build

CMakeFiles/projet_IF2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\projet_IF2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/projet_IF2.dir/clean

CMakeFiles/projet_IF2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\fanig\Documents\GitHub\projet_IF2 C:\Users\fanig\Documents\GitHub\projet_IF2 C:\Users\fanig\Documents\GitHub\projet_IF2\cmake-build-debug C:\Users\fanig\Documents\GitHub\projet_IF2\cmake-build-debug C:\Users\fanig\Documents\GitHub\projet_IF2\cmake-build-debug\CMakeFiles\projet_IF2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/projet_IF2.dir/depend

