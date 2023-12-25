cmake_minimum_required(VERSION 3.5)

project(leetcode2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions(
#     -D__SOLUTION_DEV=1
# )

set(INCLUDES
    logger.hpp
    Solution.hpp
)

set(SOURCES
    main.cpp
    logger.cpp
    Solution.cpp
    tmpl.cpp
    find-first-and-last-position-of-element-in-sorted-array.cpp
    longest-valid-parentheses.cpp
    next-permutation.cpp
    sliding-window-max.cpp
    search-in-matrix.cpp
    division-wo-division.cpp
    buy-sell-max-profit.cpp
    search-in-rotated-array.cpp
)

set(CURRENT_TASK_NAME next-permutation)
set(CURRENT_TASK_METHOD nextPermutation)

set(RESOURCES
    problems.py
    test_input.json
    README.md
)

add_executable(leetcode2 ${INCLUDES} ${SOURCES} ${RESOURCES})

target_compile_definitions(leetcode2
    PRIVATE
    __SOLUTION_DEV=1
    __CURRENT_TASK_METHOD=${CURRENT_TASK_METHOD}
    __CURRENT_TASK_NAME="${CURRENT_TASK_NAME}"
    __CURRENT_TASK_TEST=test_${CURRENT_TASK_METHOD}
)