#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
#define METHOD_NAME LEETCODE_METHOD_NAME
class Solution {
public:
    METHOD_RETURN METHOD_NAME(METHOD_PARAMS);

};
#endif

METHOD_RETURN Solution::METHOD_NAME(METHOD_PARAMS) {

}


int Solution::test_METHOD_NAME() {

    return 0;
}
