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

vector<int> Solution::slidingWindowMax(vector<int>& nums, int k) {

}


int Solution::test_slidingWindowMax() {

    return 0;
}
