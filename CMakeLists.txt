cmake_minimum_required(VERSION 3.0)
project(tre) # Name of the project

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -pthread -g") # C++14 mode
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic") # Enambles all warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always") # Color output

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

include_directories(include/) # all includes are here

# ============ GEOMETRY LIBRARY ==============

# POINT & centroids
set(DIR_SOURCES_POINT "src/point")
file(GLOB SOURCES_POINT "${DIR_SOURCES_POINT}/*.cpp") # adds all cpp files
add_library(point ${SOURCES_POINT}) # creates the point library
add_executable(geometry_test src/interface/point_test.cpp)
target_link_libraries(geometry_test point) # todo: archive geometry

# ============================================

find_package(OpenCV REQUIRED) # Required opencv for this project

# ============== IMAGE LIBRARY ===============
set(DIR_SOURCES_IMAGE "src/image")
file(GLOB SOURCES_IMAGE ${DIR_SOURCES_IMAGE}/*.cpp)
add_library(image ${SOURCES_IMAGE})
target_link_libraries(image ${OpenCV_LIBS} point)
# ============================================

# ============== MODEL LIBRARY ===============
set(DIR_SOURCES_MODEL "src/models")
file(GLOB SOURCES_MODEL ${DIR_SOURCES_MODEL}/*.cpp)
add_library(model ${SOURCES_MODEL})
target_link_libraries(model image point)
# ============================================

# ============= DATASET LIBRARY ==============
set(DIR_SOURCES_DATASET "src/dataset")
file(GLOB SOURCES_DATASET ${DIR_SOURCES_DATASET}/*.cpp)
add_library(dataset ${SOURCES_DATASET})
target_link_libraries(dataset ${OpenCV_LIBS}) # link against OpenCV libs
# ============================================

add_executable(image_test src/interface/image_test.cpp) # Compiles the executable
target_link_libraries(image_test model image dataset)


#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})
set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY SDL2)

include_directories(${SDL2_INCLUDE_DIR})

# ============ GRAPHICS LIBRARY =============
set(DIR_SOURCES_GRAPHICS "src/graphics")
file(GLOB SOURCES_GRAPHICS ${DIR_SOURCES_GRAPHICS}/*.cpp)
add_library(graphics ${SOURCES_GRAPHICS})
target_link_libraries(graphics ${SDL2_LIBRARY}) # link against SDL2 libs
# ============================================


add_executable(graphics_test src/interface/graphics_test.cpp) # Compiles the executable
target_link_libraries(graphics_test graphics image ${OpenCV_LIBS} point)
