#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "logger.hpp"

#ifdef LOGGER_NAME
static Logger LOGGER_NAME;
#endif

#define ADD_CASE(CASE_NAME, RET_TYPE, ...) RET_TYPE CASE_NAME(__VA_ARGS__); int test_ ## CASE_NAME();

#define TEST_CASE(CASE_NAME) (Solution().test_ ## CASE_NAME())

#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Solution {
public:
    ADD_CASE(divide, int, int, int);
    ADD_CASE(maxProfit, int, std::vector<int>&);
};

#endif // SOLUTION_HPP
