# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/emeric/Master_2/Synthese_Image/sia_td5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emeric/Master_2/Synthese_Image/sia_td5/build

# Utility rule file for generate.

# Include the progress variables for this target.
include ext/glbinding/codegeneration/CMakeFiles/generate.dir/progress.make

generate: ext/glbinding/codegeneration/CMakeFiles/generate.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating OpenGL binding code."
	cd /home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding/codegeneration && /usr/bin/python scripts/generate.py -s gl.xml -p patch.xml -d ../source/glbinding -r gl.revision
.PHONY : generate

# Rule to build all files generated by this target.
ext/glbinding/codegeneration/CMakeFiles/generate.dir/build: generate

.PHONY : ext/glbinding/codegeneration/CMakeFiles/generate.dir/build

ext/glbinding/codegeneration/CMakeFiles/generate.dir/clean:
	cd /home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/codegeneration && $(CMAKE_COMMAND) -P CMakeFiles/generate.dir/cmake_clean.cmake
.PHONY : ext/glbinding/codegeneration/CMakeFiles/generate.dir/clean

ext/glbinding/codegeneration/CMakeFiles/generate.dir/depend:
	cd /home/emeric/Master_2/Synthese_Image/sia_td5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emeric/Master_2/Synthese_Image/sia_td5 /home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding/codegeneration /home/emeric/Master_2/Synthese_Image/sia_td5/build /home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/codegeneration /home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/codegeneration/CMakeFiles/generate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ext/glbinding/codegeneration/CMakeFiles/generate.dir/depend
