#include <iostream>

using namespace std;

#define LOGGER_NAME LOG
#include "logger.hpp"
Logger LOG("leetcode.log", &std::cerr);

class Solution {
public:
    int divide(int dividend, int divisor) {

        if(1 == divisor)
            return dividend;

        if(-1 == divisor) {

            if(-(1L<<31) == dividend)
                return (1L<<31)-1;

            return -dividend;
        }

        if(divisor == dividend)
            return 1;

        bool minus = (dividend < 0) != (divisor < 0);

        int64_t _dividend = dividend < 0 ? -int64_t(dividend) : dividend;
        int64_t _divisor = divisor < 0 ? -int64_t(divisor) : divisor;

        if(_divisor > _dividend)
            return 0;

//        if(_divisor == _dividend)
//            return minus ? -1 : 1;

        int result = 0;
        for(; _dividend>=_divisor;) {

            int k=0;
            for(; (_divisor<<k)<=_dividend; ++k);

            _dividend  -= _divisor<<(k-1);
            result += (1<<(k-1));
        }

        return minus ? -result : result;
    }
};

int main()
{

#if 0
    int A = -2147483648;
    int B = -1;
    LOGV(A);
    LOGV(B);
    LOGV(A/B);
    LOGV(Solution().divide(A, B));
    return 0;
#endif
    const int MIN_INT = -(1L<<31);
    const int MAX_INT = (1L<<31)-1;
    for(int i=MIN_INT; i<=MAX_INT; ++i) {

        if((i>>15)<<15 == i)
            LOGV(i);
        for(int j=-10; j<10; ++j) {

//            LOGV(i);
//            LOGV(j);

            if(!j)
                continue;

            if(MIN_INT == i && -1 == j)
                continue;

//            LOGV(i/j);
//            LOGV(Solution().divide(i, j));
//            LOGV(i/j == Solution().divide(i, j));

            if(i/j != Solution().divide(i, j))
                return -1;
        }
    }

    return 0;
}
