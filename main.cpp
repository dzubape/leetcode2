#include <iostream>

using namespace std;

#include "Solution.hpp"

#include "logger.hpp"
#define LOGGER_NAME LOG
Logger LOG("leetcode.log", &std::cerr);

int main()
{
    // return TEST_CASE(nextPermutation);
    LOG << "Current case: " << __CURRENT_TASK_NAME << '\n';
    Solution solution;
    solution.setTestInputFor(__CURRENT_TASK_NAME);
    return solution.runTest(__CURRENT_TASK_NAME);
}
