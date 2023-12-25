/// task link: https://leetcode.com/problems/longest-valid-parentheses/

#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
#define longestValidParentheses longestValidParentheses
class Solution {
public:
    int longestValidParentheses(string s);

};
#endif

int Solution::longestValidParentheses(string s) {

    return 0;
}

#ifdef __SOLUTION_DEV
int Solution::test_longestValidParentheses() {

    for(auto jsonCaseInput : m_testInputData) {
        LOG << "===============";
        std::string str;
        int answer;
        jsonCaseInput[0].get_to(str);
        jsonCaseInput[1].get_to(answer);
        LOGV(str);
        LOGV(answer);

        int resp = longestValidParentheses(str);
        LOGV(resp);
        bool ok = resp == answer;
        LOG << (ok ? "SUCCEED" : "FAILED");
    }

    return 0;
}
#endif
