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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hasbi/CLionProjects/engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hasbi/CLionProjects/engine/build

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/codegen:
.PHONY : CMakeFiles/engine.dir/codegen

CMakeFiles/engine.dir/easy_image.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/easy_image.cc.o: /Users/hasbi/CLionProjects/engine/easy_image.cc
CMakeFiles/engine.dir/easy_image.cc.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/easy_image.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/easy_image.cc.o -MF CMakeFiles/engine.dir/easy_image.cc.o.d -o CMakeFiles/engine.dir/easy_image.cc.o -c /Users/hasbi/CLionProjects/engine/easy_image.cc

CMakeFiles/engine.dir/easy_image.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/easy_image.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hasbi/CLionProjects/engine/easy_image.cc > CMakeFiles/engine.dir/easy_image.cc.i

CMakeFiles/engine.dir/easy_image.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/easy_image.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hasbi/CLionProjects/engine/easy_image.cc -o CMakeFiles/engine.dir/easy_image.cc.s

CMakeFiles/engine.dir/engine.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/engine.cc.o: /Users/hasbi/CLionProjects/engine/engine.cc
CMakeFiles/engine.dir/engine.cc.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/engine.dir/engine.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/engine.cc.o -MF CMakeFiles/engine.dir/engine.cc.o.d -o CMakeFiles/engine.dir/engine.cc.o -c /Users/hasbi/CLionProjects/engine/engine.cc

CMakeFiles/engine.dir/engine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/engine.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hasbi/CLionProjects/engine/engine.cc > CMakeFiles/engine.dir/engine.cc.i

CMakeFiles/engine.dir/engine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/engine.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hasbi/CLionProjects/engine/engine.cc -o CMakeFiles/engine.dir/engine.cc.s

CMakeFiles/engine.dir/ini_configuration.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/ini_configuration.cc.o: /Users/hasbi/CLionProjects/engine/ini_configuration.cc
CMakeFiles/engine.dir/ini_configuration.cc.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/engine.dir/ini_configuration.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/ini_configuration.cc.o -MF CMakeFiles/engine.dir/ini_configuration.cc.o.d -o CMakeFiles/engine.dir/ini_configuration.cc.o -c /Users/hasbi/CLionProjects/engine/ini_configuration.cc

CMakeFiles/engine.dir/ini_configuration.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/ini_configuration.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hasbi/CLionProjects/engine/ini_configuration.cc > CMakeFiles/engine.dir/ini_configuration.cc.i

CMakeFiles/engine.dir/ini_configuration.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/ini_configuration.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hasbi/CLionProjects/engine/ini_configuration.cc -o CMakeFiles/engine.dir/ini_configuration.cc.s

CMakeFiles/engine.dir/l_parser.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/l_parser.cc.o: /Users/hasbi/CLionProjects/engine/l_parser.cc
CMakeFiles/engine.dir/l_parser.cc.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/engine.dir/l_parser.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/l_parser.cc.o -MF CMakeFiles/engine.dir/l_parser.cc.o.d -o CMakeFiles/engine.dir/l_parser.cc.o -c /Users/hasbi/CLionProjects/engine/l_parser.cc

CMakeFiles/engine.dir/l_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/l_parser.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hasbi/CLionProjects/engine/l_parser.cc > CMakeFiles/engine.dir/l_parser.cc.i

CMakeFiles/engine.dir/l_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/l_parser.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hasbi/CLionProjects/engine/l_parser.cc -o CMakeFiles/engine.dir/l_parser.cc.s

CMakeFiles/engine.dir/vector3d.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/vector3d.cc.o: /Users/hasbi/CLionProjects/engine/vector3d.cc
CMakeFiles/engine.dir/vector3d.cc.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/engine.dir/vector3d.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/vector3d.cc.o -MF CMakeFiles/engine.dir/vector3d.cc.o.d -o CMakeFiles/engine.dir/vector3d.cc.o -c /Users/hasbi/CLionProjects/engine/vector3d.cc

CMakeFiles/engine.dir/vector3d.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/vector3d.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hasbi/CLionProjects/engine/vector3d.cc > CMakeFiles/engine.dir/vector3d.cc.i

CMakeFiles/engine.dir/vector3d.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/vector3d.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hasbi/CLionProjects/engine/vector3d.cc -o CMakeFiles/engine.dir/vector3d.cc.s

CMakeFiles/engine.dir/face.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/face.cpp.o: /Users/hasbi/CLionProjects/engine/face.cpp
CMakeFiles/engine.dir/face.cpp.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/engine.dir/face.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/face.cpp.o -MF CMakeFiles/engine.dir/face.cpp.o.d -o CMakeFiles/engine.dir/face.cpp.o -c /Users/hasbi/CLionProjects/engine/face.cpp

CMakeFiles/engine.dir/face.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/face.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hasbi/CLionProjects/engine/face.cpp > CMakeFiles/engine.dir/face.cpp.i

CMakeFiles/engine.dir/face.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/face.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hasbi/CLionProjects/engine/face.cpp -o CMakeFiles/engine.dir/face.cpp.s

CMakeFiles/engine.dir/figure.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/figure.cpp.o: /Users/hasbi/CLionProjects/engine/figure.cpp
CMakeFiles/engine.dir/figure.cpp.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/engine.dir/figure.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/figure.cpp.o -MF CMakeFiles/engine.dir/figure.cpp.o.d -o CMakeFiles/engine.dir/figure.cpp.o -c /Users/hasbi/CLionProjects/engine/figure.cpp

CMakeFiles/engine.dir/figure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/figure.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hasbi/CLionProjects/engine/figure.cpp > CMakeFiles/engine.dir/figure.cpp.i

CMakeFiles/engine.dir/figure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/figure.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hasbi/CLionProjects/engine/figure.cpp -o CMakeFiles/engine.dir/figure.cpp.s

# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/easy_image.cc.o" \
"CMakeFiles/engine.dir/engine.cc.o" \
"CMakeFiles/engine.dir/ini_configuration.cc.o" \
"CMakeFiles/engine.dir/l_parser.cc.o" \
"CMakeFiles/engine.dir/vector3d.cc.o" \
"CMakeFiles/engine.dir/face.cpp.o" \
"CMakeFiles/engine.dir/figure.cpp.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

engine: CMakeFiles/engine.dir/easy_image.cc.o
engine: CMakeFiles/engine.dir/engine.cc.o
engine: CMakeFiles/engine.dir/ini_configuration.cc.o
engine: CMakeFiles/engine.dir/l_parser.cc.o
engine: CMakeFiles/engine.dir/vector3d.cc.o
engine: CMakeFiles/engine.dir/face.cpp.o
engine: CMakeFiles/engine.dir/figure.cpp.o
engine: CMakeFiles/engine.dir/build.make
engine: CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/hasbi/CLionProjects/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine
.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd /Users/hasbi/CLionProjects/engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hasbi/CLionProjects/engine /Users/hasbi/CLionProjects/engine /Users/hasbi/CLionProjects/engine/build /Users/hasbi/CLionProjects/engine/build /Users/hasbi/CLionProjects/engine/build/CMakeFiles/engine.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/engine.dir/depend

