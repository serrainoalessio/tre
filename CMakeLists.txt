cmake_minimum_required(VERSION 3.0)
project(tre) # Name of the project

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include_directories(include/) # all includes are here

# ============ GEOMETRY LIBRARY ==============

# POINT
# set(DIR_SOURCES_POINT "src/point")
# file(GLOB SOURCES_POINT ${DIR_SOURCES_POINT}/*.cpp) # adds all cpp files
# add_library(point, ${SOURCES_POINT}) # creates the point library

# ==========================================

# IMAGE
find_package(OpenCV REQUIRED) # Required opencv for this project

set(DIR_SOURCES_IMAGE "src/image")
file(GLOB SOURCES_IMAGE ${DIR_SOURCES_IMAGE}/*.cpp)
add_library(image, ${SOURCES_IMAGE})
link_target_libraries(image ${OpenCV_LIBS}) # link against OpenCV libs
add_executable(image_test src/image_test.cpp) # Compiles the executable
link_target_libraries(image_test image) # Links the image library
# ==========================================

add_executable(example src/interface/example.cpp)
