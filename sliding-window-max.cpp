#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
#define slidingWindowMax maxSlidingWindow
class Solution {
public:
    vector<int> slidingWindowMax(vector<int>& nums, int k);

};
#endif

typedef size_t SIZE_t;

vector<int> Solution::slidingWindowMax(vector<int>& nums, int k) {

    vector<int> result(nums.size()-k+1);
    int currentMaxValue = -(1L<<31);
    SIZE_t currentMaxIdx(-1);

    for(SIZE_t i=k-1; i<nums.size(); ++i) {

        LOGV(i);

        if(currentMaxIdx > i - k) {

            if(nums[i] > currentMaxValue) {

                currentMaxIdx = i;
                currentMaxValue = nums[i];
            }

            result[i-k+1] = currentMaxValue;

            continue;
        }

        LOG << "review";
        currentMaxValue = -(1L<<31);
        
        for(SIZE_t j=i-k+1; j<=i; ++j) {

            if(nums[j] > currentMaxValue) {

                currentMaxIdx = j;
                currentMaxValue = nums[j];
            }
        }

        result[i-k+1] = currentMaxValue;
    }

    return result;
}

#ifdef __SOLUTION_DEV
int Solution::test_slidingWindowMax() {

    const int k = 3;
    const int n = (k + 2) * 3;
    vector<int> nums(n, 0);
    nums[k+1] = 1;
    nums[2*(k+1)] = 1;
    auto result = slidingWindowMax(nums, k);
    LOGV(k);
    LOGV(n);
    LOGV(nums);
    LOGV(result);
    return 0;
}
#endif
