cmake_minimum_required(VERSION 3.24)
project(huff_my_file)

set(CMAKE_CXX_STANDARD 17)

add_executable(huff_my_file src/huff.cpp src/models/PriorityQueue.h src/models/PriorityQueue.cpp src/util/compress.h src/util/compress.cpp src/models/Node.h src/models/Node.cpp src/util/helpers.h src/util/helpers.cpp)
