#include <inttypes.h>

#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE) ()
class Solution {
public:
    int divide(int, int);

};
#endif

int Solution::test_divide() {

    const int MIN_INT = -1000;
    const int MAX_INT = 1000;
    for(int i=MIN_INT; i<=MAX_INT; ++i) {

        if((i>>15)<<15 == i)
            LOGV(i);
        for(int j=-10; j<10; ++j) {

            LOGV(i);
            LOGV(j);

            if(!j)
                continue;

            if(MIN_INT == i && -1 == j)
                continue;

            LOGV(i/j);
            LOGV(Solution().divide(i, j));
            LOGV(i/j == Solution().divide(i, j));

            if(i/j != Solution().divide(i, j))
                return -1;
        }
    }

    return 0;
}

int Solution::divide(int dividend, int divisor) {

    constexpr const int _INT_MIN = -(1L<<31);
    constexpr const int _INT_MAX = (1L<<31) - 1;

    if(1 == divisor)
        return dividend;

    if(-1 == divisor) {

        if(_INT_MIN == dividend)
            return _INT_MAX;

        return -dividend;
    }

    if(divisor == dividend)
        return 1;

#define ABS(VALUE) (VALUE < 0 ? -VALUE : VALUE)

    if(ABS(int64_t(divisor)) > ABS(int64_t(dividend)))
        return 0;

    bool minus = (dividend < 0) != (divisor < 0);

    if(ABS(int64_t(divisor)) == ABS(int64_t(dividend)))
        return minus ? -1 : 1;

    int appendix=0;

    if(dividend < 0) {

        appendix = 1;
        dividend = -(dividend + appendix);
    }

    divisor = ABS(divisor);

    int result = 0;
    for(; dividend>=divisor;) {

        int k=0;
        for(; divisor<=(dividend>>k); ++k);

        dividend  -= divisor<<(k-1);
        if(appendix) {

            dividend += appendix;
            appendix = 0;
        }
        result += (1<<(k-1));
    }

    return minus ? -result : result;
}
