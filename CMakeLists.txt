cmake_minimum_required(VERSION 3.5)

project(leetcode2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-D__SOLUTION_DEV)

set(INCLUDES
    logger.hpp
    Solution.hpp
)

set(SOURCES
    main.cpp
    division-wo-division.cpp
    logger.cpp
)

add_executable(leetcode2 ${INCLUDES} ${SOURCES})
