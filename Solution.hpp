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
#include <list>
#include <string>
#include <iterator>
#include <chrono>

using namespace std;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

json getTestInput(const std::string& filepath="test_input.json");

#define METHOD_RETURN int
#define METHOD_PARAMS void

class Solution {
    struct {
        uint32_t value;
        std::string units;
    } m_duration;

    std::string m_testInputFilepath;
    json m_testInputData;

    void printDuration();
public:
    Solution(const std::string &testInputFilepath="");
    int runTest(const std::string &taskName, const std::string testInputFilepath="");
#if 0
    template<typename _Ret, typename _Method, typename... _Params>
    _Ret timingRunner(_Method f, _Params... params) {

        auto start = chrono::system_clock::now();
        auto result = (this->*f)(params ...);
        auto end = chrono::system_clock::now();
        auto duration = end - start;
        auto durationMcs = chrono::duration_cast<chrono::microseconds>(duration);
        LOGV(durationMcs);
        return result;
    }
#else
    void setTestInputFile(const std::string &filepath);
    void setTestInputFor(const std::string &caseName);
    template<typename _Ret, typename... _Params>
    _Ret timingRunner(_Ret (Solution::*f)(_Params...), _Params... params) {

        auto start = chrono::system_clock::now();
        auto result = (this->*f)(params...);
        auto end = chrono::system_clock::now();
        auto duration = end - start;
        auto durationMcs = chrono::duration_cast<chrono::microseconds>(duration);
        m_duration.value = durationMcs.count();
        m_duration.units = "mics";
        printDuration();
        return result;
    }
#endif
    // CASES //
    ADD_CASE(nextPermutation, ESCAPE_COMMAS(void), vector<int>& nums);
    ADD_CASE(slidingWindowMax, ESCAPE_COMMAS(vector<int>), vector<int>& nums, int k);
    ADD_CASE(search_in_matrix, ESCAPE_COMMAS(bool), vector<vector<int>>&, int);
    ADD_CASE(divisionWoDivision, int, int, int);
    ADD_CASE(buySellMaxProfit, int, std::vector<int>&);
    ADD_CASE(searchInRotatedArray, int, std::vector<int>&, int);
    ADD_CASE(METHOD_NAME, METHOD_RETURN, METHOD_PARAMS);
};

#endif // SOLUTION_HPP
