cmake_minimum_required(VERSION 3.5)

project(leetcode2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDES logger.hpp)

set(SOURCES main.cpp logger.cpp)

add_executable(leetcode2 ${INCLUDES} ${SOURCES})
