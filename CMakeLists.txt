cmake_minimum_required(VERSION 3.20)
project(DeFiGraphEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto")

include_directories(include)

add_executable(graph_engine src/main.cpp src/ArenaAllocator.cpp src/Graph.cpp src/Solver.cpp)
