#include <iostream>

using namespace std;

#include "Solution.hpp"

#include "logger.hpp"
#define LOGGER_NAME LOG
Logger LOG("leetcode.log", &std::cerr);

int main()
{
    return TEST_CASE(nextPermutation);
}
