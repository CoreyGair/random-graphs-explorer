cmake_minimum_required(VERSION 3.19)

project(random-graphs-explorer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Python3 COMPONENTS Development NumPy)

# define for multithreading
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB_RECURSE sources src/*.cpp)

file(GLOB_RECURSE includes include/*.h)

add_executable(random-graphs-explorer ${sources} ${includes})

target_include_directories(random-graphs-explorer PUBLIC include PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS} vendor/matplotlib-cpp)

target_link_libraries(random-graphs-explorer Python3::Python Python3::NumPy)