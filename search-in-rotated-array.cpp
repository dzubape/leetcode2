#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE) (false)
#define searchInRotatedArray search
class Solution {
public:
    int searchInRotatedArray(vector<int>&, int);

};
#endif

typedef int16_t SIZE_t;

static SIZE_t searchInSortedArray(std::vector<int> &nums, int target, SIZE_t bottom=0, SIZE_t top=-1) {

    top = top<0 ? nums.size()-1 : top;

    if(nums[bottom] == target)
        return bottom;

    if(nums[top] == target)
        return top;

    while(top-bottom>1) {

        const SIZE_t middle = (bottom + top)>>1;

        if(nums[middle] == target) {

            return middle;
        }
        else if(nums[middle] > target) {

            top = middle;
        }
        else
            bottom = middle;
//        LOG << '{' << bottom << ", " << top << "}";
    }

    return -1;
}

int Solution::searchInRotatedArray(std::vector<int> &nums, int target) {


    if(nums.size() == 1)
        return nums[0] == target ? 0 : -1;

    // rotated array
    // max and min are hidden
    SIZE_t bottom;
    SIZE_t top;

    bottom=0;
    top=nums.size()-1;

    if(nums[bottom] == target)
        return bottom;

    if(nums[top] == target)
        return top;

    for(; top-bottom>1;) {

        SIZE_t middle = (bottom + top)>>1;

        if(nums[middle] < nums[top]) {

            top = middle;
        }
        else {

            bottom = middle;
        }
    }
    LOGV(top);

    if(nums[top] < nums[bottom]) {

        const SIZE_t rotationIdx = top;

        if(target >= nums[0])
            return searchInSortedArray(nums, target, 0, rotationIdx-1);

        return searchInSortedArray(nums, target, rotationIdx);
    }

    return searchInSortedArray(nums, target);
}

int Solution::test_searchInRotatedArray() {

    const SIZE_t size = 47;
    std::vector<int> nums(47, 0);

    const SIZE_t rotationIdx = 15;

    for(SIZE_t i=0; i<size; ++i) {

        nums[i] = 3 * (i >= rotationIdx ? i-rotationIdx : size-rotationIdx+i);
        LOG << '[' << i << "]: " << nums[i];
    }

//    for(SIZE_t i=0; i<size; ++i)
//        nums[i] = i;
//    nums = {4,5,6,7,0,1,2};

    LOGV(searchInRotatedArray(nums, 63));

    return 0;
}
