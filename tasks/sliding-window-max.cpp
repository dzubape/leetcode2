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

typedef int32_t SIZE_t;
typedef int16_t VALUE_t;

#if 0
#define TEST_OUTPUT "brute_force.json"
vector<int> Solution::slidingWindowMax(vector<int>& nums, int k) {

    vector<int> result(nums.size()-k+1);
    int currentMaxValue = (1L<<31)-1;
    SIZE_t currentMaxIdx(-1);

    int secondMaxValue = -(1L<<31);
    SIZE_t secondMaxIdx(-1);

    SIZE_t reviewCounter =0;

    for(SIZE_t i=k-1; i<nums.size(); ++i) {

        // LOGV(i);

        // current max still within window
        if(currentMaxIdx >= i-k+1) {

            if(nums[i] > currentMaxValue) {

                currentMaxIdx = i;
                currentMaxValue = nums[i];
            }
        }
        else if(nums[i] >= currentMaxValue) {

            currentMaxValue = nums[i];
            currentMaxIdx = i;
        }
        else {
            // LOG << "review";
            ++reviewCounter;
            currentMaxValue = -(1L<<31);
            
            for(SIZE_t j=i-k+1; j<=i; ++j) {

                if(nums[j] > currentMaxValue) {

                    currentMaxIdx = j;
                    currentMaxValue = nums[j];
                }
            }
        }

        result[i-k+1] = currentMaxValue;
    }

    LOGV(reviewCounter);

    return result;
}
#elif 1
#define TEST_OUTPUT "optimized_pop.json"
vector<int> Solution::slidingWindowMax(vector<int>& nums, int k) {

    vector<int> result(nums.size()-k+1);

    map<VALUE_t, SIZE_t> tail;

    for(SIZE_t i=0; i<k; ++i) {

        tail[nums[i]] = i;
    }

    // i is the last member in a window
    SIZE_t popCounter = 0;
    for(SIZE_t i=k-1; i<nums.size(); ++i) {

        if(i-k >= 0) {

            auto it = tail.find(nums[i-k]);
            if(it->second == i-k) {

                tail.erase(it);
                ++popCounter;
            }
        }

        tail[nums[i]] = i;
        result[i-k+1] = tail.rbegin()->first;
    }
    LOGV(popCounter);

    return result;
}
#elif 1
#define TEST_OUTPUT "map_sorted.json"
vector<int> Solution::slidingWindowMax(vector<int>& nums, int k) {

    vector<int> result(nums.size()-k+1);

    map<VALUE_t, SIZE_t> tail;

    for(SIZE_t i=0; i<k; ++i) {

        tail[nums[i]] = i;
    }

    // i is the last member in a window
    for(SIZE_t i=k-1; i<nums.size(); ++i) {

        tail[nums[i]] = i;

        for(auto it=--tail.end(); it != tail.begin(); --it) {

            if(i-k+1 <= it->second) 
                break;

            // clearing cache with obsolete values
            it = tail.erase(it);
        }

        result[i-k+1] = tail.rbegin()->first;
    }

    return result;
}
#endif

#ifdef __SOLUTION_DEV
int Solution::test_slidingWindowMax() {

#if 0
    map<int, int> test;
    test[6] = 66;
    // test[-2] = 22;
    // test[5] = 55;
    LOGV(test.rbegin()->first);
    return 0;
#endif

    int k = 3;
    const int n = (k + 2) * 3;
    vector<int> nums(n, 0);
    nums[k+1] = 1;
    nums[2*(k+1)] = 1;

    getTestInput("../test_input.json").get_to(nums);
    k = 5000;

    vector<int> result = timingRunner<vector<int>, vector<int>&, int>(
        &Solution::slidingWindowMax,
        nums,
        k
    );

    auto outputJson = json(result);
    auto ofs = ofstream("./" TEST_OUTPUT);
    ofs << outputJson;
    ofs.close();

    LOGV(k);
    LOGV(n);
    // LOGV(nums);
    // LOGV(result);
    printDuration();
    return 0;
}
#endif
