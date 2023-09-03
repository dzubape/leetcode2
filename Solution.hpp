#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "logger.hpp"

#ifdef LOGGER_NAME
static Logger LOGGER_NAME;
#endif

#define ADD_CASE(CASE_NAME, RET_TYPE, ...) RET_TYPE CASE_NAME(__VA_ARGS__); int test_ ## CASE_NAME();
#define ESCAPE_COMMAS(...) __VA_ARGS__

#define TEST_CASE(CASE_NAME) (Solution().test_ ## CASE_NAME())

#include <vector>
#include <map>
#include <string>

using namespace std;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define METHOD_RETURN int
#define METHOD_PARAMS void

class Solution {
public:
    // CASES //
    ADD_CASE(search_in_matrix, ESCAPE_COMMAS(bool), vector<vector<int>>&, int);
    ADD_CASE(divide, int, int, int);
    ADD_CASE(maxProfit, int, std::vector<int>&);
    ADD_CASE(searchInRotatedArray, int, std::vector<int>&, int);
    ADD_CASE(METHOD_NAME, METHOD_RETURN, METHOD_PARAMS);
};

#endif // SOLUTION_HPP
