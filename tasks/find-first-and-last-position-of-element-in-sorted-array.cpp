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

typedef int value_t;
typedef int length_t;

template<typename Value, typename Pos=size_t>
Pos searchAnyValuePos(const std::vector<Value> &values, const Value& searchValue, Pos left=0, Pos right=-1) {
    if(values.empty())
        return -1;
    if(right=-1)
        right = values.size()-1;
    if(values[left] == searchValue)
        return left;
    if(values[right] == searchValue)
        return right;
    while(left<right) {
        Pos middle = (left + right) >> 1;
        if(values[middle] == searchValue)
            return middle;
        // *(values[middle] < searchValue ? &left : &right) = middle;
        if(values[middle] < searchValue)
            left = middle;
        else
            right = middle;
    }
    return -1;
}

template<typename Value, typename Pos=size_t>
Pos searchLeftValuePos(const std::vector<Value> &values, const Value& searchValue, Pos left=0, Pos right=-1) {
    if(values.empty())
        return -1;
    if(right=-1)
        right = values.size()-1;
    if(values[left] == searchValue)
        return left;
    while(left+1<right) {
        Pos middle = (left + right) >> 1;
        if(values[middle] >= searchValue)
            right = middle;
        else
            left = middle;
    }
    if(values[left] == searchValue)
        return left;
    if(values[right] == searchValue)
        return right;
    return -1;
}

template<typename Value, typename Pos=size_t>
Pos searchRightValuePos(const std::vector<Value> &values, const Value& searchValue, Pos left=0, Pos right=-1) {
    if(values.empty())
        return -1;
    if(right=-1)
        right = values.size()-1;
    if(values[right] == searchValue)
        return right;
    while(left+1<right) {
        Pos middle = (left + right) >> 1;
        if(values[middle] <= searchValue)
            left = middle;
        else
            right = middle;
    }
    if(values[right] == searchValue)
        return right;
    if(values[left] == searchValue)
        return left;
    return -1;
}


vector<int> Solution::findFirstAndLastPositionOfElementInSortedArray(vector<int>& nums, int target) {
    vector<int> result;

    length_t center = searchAnyValuePos(nums, target);

    if(center < 0)
        return {-1, -1};

    length_t left = searchLeftValuePos(nums, target, 0, center);
    length_t right = searchRightValuePos(nums, target, center);
    
    return {left, right};
}

#ifdef __SOLUTION_DEV
int Solution::test_findFirstAndLastPositionOfElementInSortedArray() {

    bool globalOk = true;
    for(size_t i=0; i<m_testInputData.size(); ++i) {
        std::vector<value_t> values;
        std::vector<length_t> realEnds;
        length_t searchValue;
        auto inputData = m_testInputData[i];
        inputData[0].get_to(values);
        inputData[1].get_to(searchValue);
        inputData[2].get_to(realEnds);
        LOGV(values);
        LOGV(searchValue);
        LOGV(realEnds);

        auto predEnds = findFirstAndLastPositionOfElementInSortedArray(values, searchValue);
        bool localOk = predEnds == realEnds;

        ~LOG;
        LOG << "> localOk: " << (localOk ? "SUCCEED" : "FAILED");
        LOG << "================";
        globalOk = globalOk && localOk;
    }

    LOG << "> globalOk: " << (globalOk ? "SUCCEED" : "FAILED");
    LOG << "++++++++++++++++";
    return 0;
}
#endif
