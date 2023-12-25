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


#include <stack>

int Solution::longestValidParentheses(string s) {
    typedef int16_t length_t;
    std::stack<length_t> tracker;
    length_t validStart = -1;
    length_t maxLength = 0;
    for(length_t i=0; i<s.length(); ++i) {
        auto c = s[i];
        if('(' == c) {
            if(validStart < 0)
                validStart = i;
            tracker.push(i);
        }
        else /*if(')' == c)*/ {
            length_t validLength = 0;
            // invalid input
            if(tracker.empty()) {
                if(validStart >= 0) {
                    validLength = i - validStart;
                    validStart = -1;
                }
                else {
                    // do nothing, wait for '('
                }
            }
            // valid input
            else {
                tracker.pop();
                if(tracker.empty()) {
                    validLength = i - validStart + 1;
                }
                else {
                    validLength = i - tracker.top();
                }
            }

            if(validLength > maxLength) {
                maxLength = validLength;
            }
        }
    }

    // if(validStart >= 0) {
    //     if(tracker.empty()) {
    //         length_t validLength = s.size() - validStart;
    //         if(validLength > maxLength) {
    //             maxLength = validLength;
    //         }
    //     }
    //     else {
    //         length_t validLength = s.size() - tracker.top() - 1;
    //         if(validLength > maxLength) {
    //             maxLength = validLength;
    //         }
    //     }
    // }
    // ")(((((()())()()))()(()))("

    return maxLength;
}

#ifdef __SOLUTION_DEV
int Solution::test_longestValidParentheses() {

    for(size_t i=0; i<m_testInputData.size(); ++i) {
        LOG << "===============";
        LOGV(i);
        auto jsonCaseInput = m_testInputData[i];
        std::string str;
        int answer;
        jsonCaseInput[0].get_to(str);
        jsonCaseInput[1].get_to(answer);
        LOGV(str);
        LOGV(answer);

        if(i == 13) {

            int _=0;
        }
        int resp = longestValidParentheses(str);
        LOGV(resp);
        bool ok = resp == answer;
        LOG << (ok ? "SUCCEED" : "FAILED");
    }

    return 0;
}
#endif
