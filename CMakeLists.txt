cmake_minimum_required(VERSION 3.5)

project(leetcode2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${PROJECT_SOURCE_DIR}
)

set(INCLUDES
    logger.hpp
    Solution.hpp
)

file(GLOB TASKS ${PROJECT_SOURCE_DIR}/tasks/*.cpp)

set(SOURCES
    main.cpp
    logger.cpp
    Solution.cpp
    ${TASKS}
)


set(RESOURCES
    problems.py
    test_input.json
    README.md
)

add_executable(leetcode2 ${INCLUDES} ${SOURCES} ${RESOURCES})

target_compile_definitions(leetcode2
    PRIVATE
    __SOLUTION_DEV=1
)