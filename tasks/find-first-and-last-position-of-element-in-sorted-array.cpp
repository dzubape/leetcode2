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

template<typename Value, typename Pos=length_t>
std::vector<Pos> searchAnyValuePosBetween(const std::vector<Value> &values, const Value& searchValue, Pos left=0, Pos right=-1) {
    if(values.empty())
        return {-1, -1, -1};
    if(right=-1)
        right = values.size()-1;
    if(values[left] == searchValue)
        return {left, left, right};
    if(values[right] == searchValue)
        return {left, right, right};
    while(left<right) {
        Pos middle = (left + right) >> 1;
        if(values[middle] == searchValue)
            return {left, middle, right};
        if(values[middle] < searchValue)
            left = middle;
        else
            right = middle;
    }
    return {-1, -1, -1};
}

template<typename Value, typename Pos=length_t>
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

template<typename Value, typename Pos=length_t>
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

template<typename Value, typename Pos=length_t>
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


vector<int> Solution::findFirstAndLastPositionOfElementInSortedArray(vector<int>& values, int target) {
    vector<length_t> result;

    vector<length_t> leftCenterRight = searchAnyValuePosBetween(values, target);
    length_t left = leftCenterRight[0];
    length_t center = leftCenterRight[1];
    length_t right = leftCenterRight[2];

    if(center < 0)
        return {-1, -1};

    left = searchLeftValuePos(values, target, left, center);
    right = searchRightValuePos(values, target, center, right);
    
    return {left, right};
}

#ifdef __SOLUTION_DEV
int Solution::test_findFirstAndLastPositionOfElementInSortedArray() {
#if 1
#define Q_MAX_VALUE 10
#define Q_MAX_COUNT 30
#define Q_MIN_COUNT 1
    std::srand(std::time(nullptr));
    bool globalOk = true;
#define isGlobalOk(predicate) globalOk = globalOk && (predicate)
    for(int q=0; q<10; ++q) {
        int size = std::rand() % (Q_MAX_COUNT - Q_MIN_COUNT) + Q_MIN_COUNT;
        std::vector<value_t> values(size);
        for(length_t i=0; i<size; ++i) {
            values[i] = std::rand() % Q_MAX_VALUE;
        }
        std::sort(values.begin(), values.end());
        length_t realSearchIdx = std::rand() % values.size();
        LOGV(values);
#if 1
        value_t searchValue = values[realSearchIdx];
        auto range = findFirstAndLastPositionOfElementInSortedArray(values, searchValue);
        LOGV(searchValue);
        LOGV(range);
        length_t start = range[0];
        length_t end = range[1];
        LOGV(values[start]);
        LOGV(values[end]);
        LOG << "~~~~~~~~";
        if(start)
            LOGV(values[start-1]);
        if(end+1<values.size())
            LOGV(values[end+1]);

        bool localOk = true;
#define isLocalOk(predicate) localOk = localOk && (predicate)
        isLocalOk(values[start] == searchValue);
        isLocalOk(values[end] == searchValue);
        if(start)
            isLocalOk(values[start-1] < searchValue);
        if(end < values.size()-1)
            isLocalOk(values[end+1] > searchValue);
        isGlobalOk(localOk);
        LOG << (localOk ? "Local SUCCESS" : "Local FAIL");
#elif 0
        auto foundIdx = searchAnyValuePos(values, values[realSearchIdx]);
        LOGV(size);
        LOGV(realSearchIdx);
        LOGV(foundIdx);
        LOGV(values[realSearchIdx]);
        LOGV(values[foundIdx]);
        LOGV(values[foundIdx] == values[realSearchIdx] ? "YES" : "NO");
#endif
        LOG << "================";
    }
    LOG << (globalOk ? "Total SUCCESS!" : "Total FAIL!");
    LOG << "++++++++++++++++";
    return 0;
#elif 1

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
#endif
}
#endif
