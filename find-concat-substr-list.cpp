#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
#define findConcatSubstrList findSubstring
class Solution {
public:
    vector<int> findConcatSubstrList(string s, vector<string>& words);

};
#endif

vector<int> Solution::findConcatSubstrList(string s, vector<string>& words) {

    return 0;
}

#ifdef __SOLUTION_DEV
int Solution::test_findConcatSubstrList() {

    return 0;
}
#endif
