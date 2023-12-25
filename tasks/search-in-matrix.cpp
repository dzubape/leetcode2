#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define search_in_matrix searchMatrix
#define LOGV(VALUE) ""
class Solution {
public:
    bool search_in_matrix(vector<vector<int>>&, int);

};
#endif

typedef ssize_t SIZE_t;

static SIZE_t searchInSortedArray(std::vector<int> &nums, int target, SIZE_t bottom=0, SIZE_t top=-1) {

    top = top < 0 ? nums.size()-1 : top;

    if(nums[bottom] == target)
        return bottom;

    while(top - bottom > 1) {

        const SIZE_t middle = (bottom + top)>>1;

        if(nums[middle] >= target)
            top = middle;
        else if(nums[bottom] == target) {

            LOGV(nums[bottom]);
            return bottom;
        }
        else
            bottom = middle;
    }
    LOGV(nums[top]);

    return nums[top] == target ? top : -1;
}

bool Solution::search_in_matrix(vector<vector<int>>& matrix, int target) {

    SIZE_t i;
    for(i=1; i<matrix.size(); ++i) {

        if(matrix[i][0] > target) {

            if(matrix[i-1][0] > target)
                return false;
            break;
        }
    }
    LOGV(i);

    return searchInSortedArray(matrix[i-1], target) >= 0;
}


int Solution::test_search_in_matrix() {

    vector<vector<int>> matrix = {{1, 1, 2, 4, 6, 6}, {6, 7, 9, 9, 11, 11}, {12, 15, 19, 33, 53, 61}};

    if(!search_in_matrix(matrix, 11))
        return -1;

    return 0;
}
