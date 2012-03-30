# CMakeLists.txt
# Main CMakeLists.txt for GUI
#
# @author Dennis J. McWherter, Jr.
# @version $Id$
cmake_minimum_required(VERSION 2.6)
project(AbstractGraph)

# Hide things we don't need
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES CMAKE_OSX_SYSROOT)
endif(APPLE)

# Basic compiler options
set(CMAKE_CXX_FLAGS "-Wall -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Wall -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -g")

# Make sure the user has Qt
find_package(Qt4 4.7 REQUIRED)
set(QT_USE_QTCORE true)
set(QT_USE_QTGUI true)
set(QT_USE_QTOPENGL true)
set(QT_USE_QTXML true)
include(${QT_USE_FILE})

# Source Files
#file(windows_SRC Windows/*.h Windows/*.cpp)
qt4_wrap_cpp(WINDOWS_MOC_SRC Windows/MainWindow.h)
set(WINDOWS_SRC Windows/MainWindow.h Windows/MainWindow.cpp)

# Main Executable
add_executable(${PROJECT_NAME} ${WINDOWS_MOC_SRC} ${WINDOWS_SRC} main.cpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${QT_INCLUDE_DIR})

# Libraries
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

