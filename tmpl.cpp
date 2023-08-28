#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
class Solution {
public:
    int tmpl(void);

};
#endif

int Solution::tmpl(void) {

}


int Solution::test_tmpl() {

}
