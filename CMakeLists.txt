cmake_minimum_required(VERSION 3.10)
project(OpenGLProject LANGUAGES CXX)

# Set the desired C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Turn off CMake log messages, but show compilation command
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Generate the executable in same folder as source files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Add all the .cpp files in the folder to the project
file(GLOB SOURCES "*.cpp")

# Define the executable
add_executable(OpenGLProject ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "/opt/homebrew/include")

# If you need to link additional libraries, you can use:
target_link_directories(${PROJECT_NAME} PRIVATE "/opt/homebrew/lib")
target_link_libraries(${PROJECT_NAME} "-lglfw" "-lglew" "-framework GLUT" "-framework OpenGL")

#set(ENV{MAKEFLAGS} "--no-print-directory")
#if(CMAKE_GENERATOR MATCHES "Makefiles")
#    set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} --no-print-directory -s")
#endif()

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set compiler flags based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=native -ftree-vectorize -ffast-math -funroll-loops")
endif()

# Your project configuration
project(OpenGLProject)
