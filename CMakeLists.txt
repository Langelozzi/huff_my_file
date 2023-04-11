cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled src/main.cpp src/models/PriorityQueue.h src/models/PriorityQueue.cpp src/util/compress.h src/util/compress.cpp src/models/Node.h src/models/Node.cpp)
