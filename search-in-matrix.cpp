#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
class Solution {
public:
    bool search_in_matrix(vector<vector<int>>&, int);

};
#endif

bool Solution::search_in_matrix(vector<vector<int>>&, int) {

}


int Solution::test_search_in_matrix() {

}
