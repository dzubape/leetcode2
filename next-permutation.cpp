#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
#define nextPermutation nextPermutation
class Solution {
public:
    void nextPermutation(vector<int>& nums);

};
#endif

void Solution::nextPermutation(vector<int>& nums) {
    auto sortear = [](const void *pa, const void *pb){
        auto &a = *((int*)pa);
        auto &b = *((int*)pb);
        return a < b ? -1 : (a == b ? 0 : 1);
    };
    typedef int8_t length_t;
    typedef int value_t;
    length_t i;
    for(i=nums.size()-1; i>0; --i) {
        if(nums[i-1] < nums[i]) {
            for(length_t j=nums.size()-1; j>=i; --j) {
                if(nums[i-1] < nums[j]) {
                    std::swap(nums[i-1], nums[j]);
                    std::qsort(nums.data() + i, nums.size() - i, sizeof(int), sortear);
                    return;
                }
            }
            break;
        }
    }
    std::qsort(nums.data(), nums.size(), sizeof(int), sortear);
    return;
}

#ifdef __SOLUTION_DEV
int Solution::test_nextPermutation() {
    // vector<vector<vector<int>>> testData;
    // getTestInput("../test_input.json").get_to(testData);
    
    auto testData = getTestInput("../test_input.json");
    LOGV(testData);
    for(size_t i=0; i<testData.size(); ++i) {
        vector<int> nums, answerNums;
        testData[i][0].get_to(nums);
        testData[i][1].get_to(answerNums);
        LOG << "---------------\n";
        LOG << "input:\n" << nums;
        nextPermutation(nums);
        LOG << "answer:\n" << nums;
        LOG << "truth:\n" << answerNums;
        LOGV(nums == answerNums);
    }

    return 0;
}
#endif
