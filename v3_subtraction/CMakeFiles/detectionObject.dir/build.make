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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction"

# Include any dependencies generated for this target.
include CMakeFiles/detectionObject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/detectionObject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/detectionObject.dir/flags.make

CMakeFiles/detectionObject.dir/main.cpp.o: CMakeFiles/detectionObject.dir/flags.make
CMakeFiles/detectionObject.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/detectionObject.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/detectionObject.dir/main.cpp.o -c "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction/main.cpp"

CMakeFiles/detectionObject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/detectionObject.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction/main.cpp" > CMakeFiles/detectionObject.dir/main.cpp.i

CMakeFiles/detectionObject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/detectionObject.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction/main.cpp" -o CMakeFiles/detectionObject.dir/main.cpp.s

CMakeFiles/detectionObject.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/detectionObject.dir/main.cpp.o.requires

CMakeFiles/detectionObject.dir/main.cpp.o.provides: CMakeFiles/detectionObject.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/detectionObject.dir/build.make CMakeFiles/detectionObject.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/detectionObject.dir/main.cpp.o.provides

CMakeFiles/detectionObject.dir/main.cpp.o.provides.build: CMakeFiles/detectionObject.dir/main.cpp.o


# Object files for target detectionObject
detectionObject_OBJECTS = \
"CMakeFiles/detectionObject.dir/main.cpp.o"

# External object files for target detectionObject
detectionObject_EXTERNAL_OBJECTS =

detectionObject: CMakeFiles/detectionObject.dir/main.cpp.o
detectionObject: CMakeFiles/detectionObject.dir/build.make
detectionObject: /usr/local/lib/libopencv_stitching.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_superres.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_videostab.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_aruco.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_bgsegm.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_bioinspired.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_ccalib.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_dpm.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_face.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_fuzzy.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_img_hash.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_line_descriptor.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_optflow.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_reg.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_rgbd.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_saliency.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_stereo.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_structured_light.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_surface_matching.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_tracking.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_xfeatures2d.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_ximgproc.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_xobjdetect.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_xphoto.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_shape.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_photo.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_calib3d.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_phase_unwrapping.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_dnn.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_video.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_datasets.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_plot.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_text.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_features2d.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_flann.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_highgui.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_ml.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_videoio.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_imgcodecs.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_objdetect.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_imgproc.3.3.0.dylib
detectionObject: /usr/local/lib/libopencv_core.3.3.0.dylib
detectionObject: CMakeFiles/detectionObject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable detectionObject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/detectionObject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/detectionObject.dir/build: detectionObject

.PHONY : CMakeFiles/detectionObject.dir/build

CMakeFiles/detectionObject.dir/requires: CMakeFiles/detectionObject.dir/main.cpp.o.requires

.PHONY : CMakeFiles/detectionObject.dir/requires

CMakeFiles/detectionObject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/detectionObject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/detectionObject.dir/clean

CMakeFiles/detectionObject.dir/depend:
	cd "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction" "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction" "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction" "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction" "/Users/rafaelalmeida/Google Drive/UA/VisualComputation/Project/v3_subtraction/CMakeFiles/detectionObject.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/detectionObject.dir/depend

