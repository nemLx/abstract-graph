# CMakeLists.txt
# Main CMakeLists.txt for GraphiX Library
#
# @author Dennis J. McWherter, Jr.
# @version $Id$
cmake_minimum_required(VERSION 2.8.6)
project(GraphiX)

# Hide things we don't need
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES CMAKE_OSX_SYSROOT)
endif(APPLE)

# Basic compiler options
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "-Wall -O0 -g")
  set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "-Wall -O3")
  set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -g")
endif(NOT WIN32)

# Need OpenGL of course
find_package(OpenGL REQUIRED)

# Source Files
set(GFX_SRC src/Gfx/Shape.cpp include/Gfx/Shape.h
  src/Gfx/Circle.cpp include/Gfx/Circle.h)
set(SCENE_SRC src/Scene/Scene.cpp include/Scene/Scene.h)

set(SOURCE_FILES ${GFX_SRC} ${SCENE_SRC} graphix.h)

# Main Binary
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Include directories
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(./include)

# Libraries
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
