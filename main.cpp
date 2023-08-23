#include <iostream>

using namespace std;

#define LOGGER_NAME LOG
#include "logger.hpp"
Logger LOG("leetcode.log", &std::cerr);

class Solution {
public:
    int divide(int dividend, int divisor) {

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

        if(abs(int64_t(divisor)) > abs(int64_t(dividend)))
            return 0;

        bool minus = (dividend < 0) != (divisor < 0);

        if(abs(int64_t(divisor)) == abs(int64_t(dividend)))
            return minus ? -1 : 1;

        int _dividend, appendix;

        if(dividend < 0) {

            appendix = 1;
            _dividend = -(dividend + appendix);
        }
        else {

            _dividend = dividend;
            appendix = 0;
        }

        int _divisor = divisor < 0 ? -divisor : divisor;

        int result = 0;
        for(; _dividend>=_divisor;) {

            int k=0;
            for(; _divisor<=(_dividend>>k); ++k);

            _dividend  -= _divisor<<(k-1);
            _dividend += appendix; appendix = 0;
            result += (1<<(k-1));
        }

        return minus ? -result : result;
    }
};

int main()
{

#if 0
    int A = -9;
    int B = 9;
    LOGV(A);
    LOGV(B);
    LOGV(A/B);
    LOGV(Solution().divide(A, B));
    return 0;
#endif

#if 1
    int A = 2147483647;
    int B = 2147483647;
    LOGV(A);
    LOGV(B);
    LOGV(A/B);
    LOGV(Solution().divide(A, B));
    return 0;
#endif

//    const int MIN_INT = -(1L<<31);
//    const int MAX_INT = (1L<<31)-1;
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
