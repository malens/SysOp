# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw

# Include any dependencies generated for this target.
include CMakeFiles/crawler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crawler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crawler.dir/flags.make

CMakeFiles/crawler.dir/dirCrawler.c.o: CMakeFiles/crawler.dir/flags.make
CMakeFiles/crawler.dir/dirCrawler.c.o: dirCrawler.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/crawler.dir/dirCrawler.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/crawler.dir/dirCrawler.c.o   -c /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw/dirCrawler.c

CMakeFiles/crawler.dir/dirCrawler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crawler.dir/dirCrawler.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw/dirCrawler.c > CMakeFiles/crawler.dir/dirCrawler.c.i

CMakeFiles/crawler.dir/dirCrawler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crawler.dir/dirCrawler.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw/dirCrawler.c -o CMakeFiles/crawler.dir/dirCrawler.c.s

CMakeFiles/crawler.dir/dirCrawler.c.o.requires:
.PHONY : CMakeFiles/crawler.dir/dirCrawler.c.o.requires

CMakeFiles/crawler.dir/dirCrawler.c.o.provides: CMakeFiles/crawler.dir/dirCrawler.c.o.requires
	$(MAKE) -f CMakeFiles/crawler.dir/build.make CMakeFiles/crawler.dir/dirCrawler.c.o.provides.build
.PHONY : CMakeFiles/crawler.dir/dirCrawler.c.o.provides

CMakeFiles/crawler.dir/dirCrawler.c.o.provides.build: CMakeFiles/crawler.dir/dirCrawler.c.o

# Object files for target crawler
crawler_OBJECTS = \
"CMakeFiles/crawler.dir/dirCrawler.c.o"

# External object files for target crawler
crawler_EXTERNAL_OBJECTS =

libcrawler.a: CMakeFiles/crawler.dir/dirCrawler.c.o
libcrawler.a: CMakeFiles/crawler.dir/build.make
libcrawler.a: CMakeFiles/crawler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libcrawler.a"
	$(CMAKE_COMMAND) -P CMakeFiles/crawler.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crawler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crawler.dir/build: libcrawler.a
.PHONY : CMakeFiles/crawler.dir/build

CMakeFiles/crawler.dir/requires: CMakeFiles/crawler.dir/dirCrawler.c.o.requires
.PHONY : CMakeFiles/crawler.dir/requires

CMakeFiles/crawler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crawler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crawler.dir/clean

CMakeFiles/crawler.dir/depend:
	cd /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw /home/malens/Desktop/sysop2/WilkoszJakub/cw02/zad2/nftw/CMakeFiles/crawler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crawler.dir/depend

