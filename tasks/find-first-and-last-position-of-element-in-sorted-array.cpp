/// task link: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array

#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
#define findFirstAndLastPositionOfElementInSortedArray searchRange
class Solution {
public:
    vector<int> findFirstAndLastPositionOfElementInSortedArray(vector<int>& nums, int target);

};
#endif

vector<int> Solution::findFirstAndLastPositionOfElementInSortedArray(vector<int>& nums, int target) {
    vector<int> result;
    return result;
}

#ifdef __SOLUTION_DEV
int Solution::test_findFirstAndLastPositionOfElementInSortedArray() {

    for(auto jsonCaseInput : m_testInputData) {

    }

    return 0;
}
#endif
