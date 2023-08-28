cmake_minimum_required(VERSION 3.5)

project(leetcode2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(
    -D__SOLUTION_DEV
)

set(INCLUDES
    logger.hpp
    Solution.hpp
)

set(SOURCES
    main.cpp
    logger.cpp
    tmpl.cpp
    division-wo-division.cpp
    buy-sell-max-profit.cpp
    search-in-rotated-array.cpp
)

set(RESOURCES
    add-problem.sh
    test_input.json
    README.md
)

add_executable(leetcode2 ${INCLUDES} ${SOURCES} ${RESOURCES})
