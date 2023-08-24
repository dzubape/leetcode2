#include <iostream>

using namespace std;

#include "logger.hpp"
Logger LOG("leetcode.log", &std::cerr);

#include "Solution.hpp"

int main()
{
    return TEST_CASE(divide);
}
