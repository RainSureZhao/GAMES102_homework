# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Cmake 3.175\cmake-3.17.5-win64-x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Cmake 3.175\cmake-3.17.5-win64-x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Games102\hw3_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Games102\hw3_test\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hw3_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw3_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw3_test.dir/flags.make

CMakeFiles/hw3_test.dir/main.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/main.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw3_test.dir/main.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\main.cpp.obj -c D:\Games102\hw3_test\main.cpp

CMakeFiles/hw3_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/main.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\main.cpp > CMakeFiles\hw3_test.dir\main.cpp.i

CMakeFiles/hw3_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/main.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\main.cpp -o CMakeFiles\hw3_test.dir\main.cpp.s

CMakeFiles/hw3_test.dir/src/glad.c.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/src/glad.c.obj: CMakeFiles/hw3_test.dir/includes_C.rsp
CMakeFiles/hw3_test.dir/src/glad.c.obj: ../src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hw3_test.dir/src/glad.c.obj"
	D:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\hw3_test.dir\src\glad.c.obj   -c D:\Games102\hw3_test\src\glad.c

CMakeFiles/hw3_test.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hw3_test.dir/src/glad.c.i"
	D:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Games102\hw3_test\src\glad.c > CMakeFiles\hw3_test.dir\src\glad.c.i

CMakeFiles/hw3_test.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hw3_test.dir/src/glad.c.s"
	D:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Games102\hw3_test\src\glad.c -o CMakeFiles\hw3_test.dir\src\glad.c.s

CMakeFiles/hw3_test.dir/imgui/imgui.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/imgui/imgui.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/imgui/imgui.cpp.obj: ../imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hw3_test.dir/imgui/imgui.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\imgui\imgui.cpp.obj -c D:\Games102\hw3_test\imgui\imgui.cpp

CMakeFiles/hw3_test.dir/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/imgui/imgui.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\imgui\imgui.cpp > CMakeFiles\hw3_test.dir\imgui\imgui.cpp.i

CMakeFiles/hw3_test.dir/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/imgui/imgui.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\imgui\imgui.cpp -o CMakeFiles\hw3_test.dir\imgui\imgui.cpp.s

CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.obj: ../imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\imgui\imgui_demo.cpp.obj -c D:\Games102\hw3_test\imgui\imgui_demo.cpp

CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\imgui\imgui_demo.cpp > CMakeFiles\hw3_test.dir\imgui\imgui_demo.cpp.i

CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\imgui\imgui_demo.cpp -o CMakeFiles\hw3_test.dir\imgui\imgui_demo.cpp.s

CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.obj: ../imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\imgui\imgui_draw.cpp.obj -c D:\Games102\hw3_test\imgui\imgui_draw.cpp

CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\imgui\imgui_draw.cpp > CMakeFiles\hw3_test.dir\imgui\imgui_draw.cpp.i

CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\imgui\imgui_draw.cpp -o CMakeFiles\hw3_test.dir\imgui\imgui_draw.cpp.s

CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.obj: ../imgui/imgui_impl_glfw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\imgui\imgui_impl_glfw.cpp.obj -c D:\Games102\hw3_test\imgui\imgui_impl_glfw.cpp

CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\imgui\imgui_impl_glfw.cpp > CMakeFiles\hw3_test.dir\imgui\imgui_impl_glfw.cpp.i

CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\imgui\imgui_impl_glfw.cpp -o CMakeFiles\hw3_test.dir\imgui\imgui_impl_glfw.cpp.s

CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.obj: ../imgui/imgui_impl_opengl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\imgui\imgui_impl_opengl3.cpp.obj -c D:\Games102\hw3_test\imgui\imgui_impl_opengl3.cpp

CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\imgui\imgui_impl_opengl3.cpp > CMakeFiles\hw3_test.dir\imgui\imgui_impl_opengl3.cpp.i

CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\imgui\imgui_impl_opengl3.cpp -o CMakeFiles\hw3_test.dir\imgui\imgui_impl_opengl3.cpp.s

CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.obj: ../imgui/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\imgui\imgui_widgets.cpp.obj -c D:\Games102\hw3_test\imgui\imgui_widgets.cpp

CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\imgui\imgui_widgets.cpp > CMakeFiles\hw3_test.dir\imgui\imgui_widgets.cpp.i

CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\imgui\imgui_widgets.cpp -o CMakeFiles\hw3_test.dir\imgui\imgui_widgets.cpp.s

CMakeFiles/hw3_test.dir/MathUtil.cpp.obj: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/MathUtil.cpp.obj: CMakeFiles/hw3_test.dir/includes_CXX.rsp
CMakeFiles/hw3_test.dir/MathUtil.cpp.obj: ../MathUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/hw3_test.dir/MathUtil.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3_test.dir\MathUtil.cpp.obj -c D:\Games102\hw3_test\MathUtil.cpp

CMakeFiles/hw3_test.dir/MathUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/MathUtil.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Games102\hw3_test\MathUtil.cpp > CMakeFiles\hw3_test.dir\MathUtil.cpp.i

CMakeFiles/hw3_test.dir/MathUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/MathUtil.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Games102\hw3_test\MathUtil.cpp -o CMakeFiles\hw3_test.dir\MathUtil.cpp.s

# Object files for target hw3_test
hw3_test_OBJECTS = \
"CMakeFiles/hw3_test.dir/main.cpp.obj" \
"CMakeFiles/hw3_test.dir/src/glad.c.obj" \
"CMakeFiles/hw3_test.dir/imgui/imgui.cpp.obj" \
"CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.obj" \
"CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.obj" \
"CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.obj" \
"CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.obj" \
"CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.obj" \
"CMakeFiles/hw3_test.dir/MathUtil.cpp.obj"

# External object files for target hw3_test
hw3_test_EXTERNAL_OBJECTS =

hw3_test.exe: CMakeFiles/hw3_test.dir/main.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/src/glad.c.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/imgui/imgui.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/imgui/imgui_demo.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/imgui/imgui_draw.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/imgui/imgui_impl_glfw.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/imgui/imgui_impl_opengl3.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/imgui/imgui_widgets.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/MathUtil.cpp.obj
hw3_test.exe: CMakeFiles/hw3_test.dir/build.make
hw3_test.exe: ../lib/glfw3.dll
hw3_test.exe: CMakeFiles/hw3_test.dir/linklibs.rsp
hw3_test.exe: CMakeFiles/hw3_test.dir/objects1.rsp
hw3_test.exe: CMakeFiles/hw3_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Games102\hw3_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable hw3_test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hw3_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw3_test.dir/build: hw3_test.exe

.PHONY : CMakeFiles/hw3_test.dir/build

CMakeFiles/hw3_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hw3_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hw3_test.dir/clean

CMakeFiles/hw3_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Games102\hw3_test D:\Games102\hw3_test D:\Games102\hw3_test\cmake-build-debug D:\Games102\hw3_test\cmake-build-debug D:\Games102\hw3_test\cmake-build-debug\CMakeFiles\hw3_test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw3_test.dir/depend
