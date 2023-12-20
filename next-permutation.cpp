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
    typedef int8_t length_t;
    typedef int value_t;
    auto sortear = [](const void *pa, const void *pb){
        auto &a = *((value_t*)pa);
        auto &b = *((value_t*)pb);
        return a < b ? -1 : (a == b ? 0 : 1);
    };
    length_t i;
    for(i=nums.size()-1; i>0; --i) {
        if(nums[i-1] < nums[i]) {
            for(length_t j=nums.size()-1; j>=i; --j) {
                if(nums[i-1] < nums[j]) {
                    std::swap(nums[i-1], nums[j]);
                    std::qsort(nums.data() + i, nums.size() - i, sizeof(value_t), sortear);
                    return;
                }
            }
            break;
        }
    }
    std::qsort(nums.data(), nums.size(), sizeof(value_t), sortear);
    return;
}

#ifdef __SOLUTION_DEV
int Solution::test_nextPermutation() {
    auto testData = getTestInput(m_testInputFilepath);
    LOGV(testData);
    bool globalOk = true;
    for(size_t i=0; i<testData.size(); ++i) {
        vector<int> nums, answerNums;
        testData[i][0].get_to(nums);
        testData[i][1].get_to(answerNums);
        LOG << "---------------";
        LOG << "input:\n" << nums << '\n';
        nextPermutation(nums);
        LOG << "answer:\n" << nums;
        LOG << "truth:\n" << answerNums;
        bool localOk = nums == answerNums;
        LOG << '\n' << (localOk ? "SUCCEED!": "FAILED!");
        globalOk = globalOk && localOk;
    }

    return globalOk ? 0 : 1;
}
#endif
