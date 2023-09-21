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

    return 0;
}

#ifdef __SOLUTION_DEV
int Solution::test_nextPermutation() {

    return 0;
}
#endif
