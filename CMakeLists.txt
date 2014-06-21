# -DSFML_ROOT="d:/lib/SFML-2.1/"

cmake_minimum_required(VERSION 2.8)
project(Arkanoid11)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# -D CMAKE_BUILD_TYPE=Release


# Compilers and CMake switches
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Set VERSION information in a config.h file
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)


# Source and headers
aux_source_directory(. SRC_LIST)
include_directories(${PROJECT_BINARY_DIR})
file(GLOB_RECURSE HEADERS *.hpp *.h)

if(NOT HEADERS)
  message(FATAL_ERROR "Headers not found!")
endif()

# Define executable, before target_link_libraries
add_executable(${PROJECT_NAME} ${SRC_LIST})

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#set(SFML_STATIC_LIBRARIES TRUE) # use static libraries
find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Cpack packing
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_NAME}_VERSION_MINOR}")
include(CPack)


##################################################################

# OpenGL
#find_package(OpenGL REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIR})
#if (OPENGL_FOUND)
#  target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
#  target_link_libraries(${PROJECT_NAME} m)  # if you use maths.h
#endif()


#set(SFML_INCLUDE "C:/lib/SFML-2.1/include")
#set(SFML_LIB "C:/lib/SFML-2.1/lib")
#include_directories(${SFML_INCLUDE})
#link_directories(${SFML_LIB})
#target_link_libraries(${PROJECT_NAME} FSML)
#add_library(FreenectDriver SHARED ${HEADERS} ${SOURCES})
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
#list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
#include_directories(${C:\lib\SFML-2.1-mingw\include\})
