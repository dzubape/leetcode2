#include <iostream>

using namespace std;

#include "Solution.hpp"

#include "logger.hpp"
#define LOGGER_NAME LOG
Logger LOG("leetcode.log", &std::cerr);

void Solution::printDuration() {
    LOG << "duration: " << m_duration.value << m_duration.units;
}

int main()
{
    return TEST_CASE(slidingWindowMax);
}
