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

            if(-(1UL<<31) == dividend)
                return (1UL<<31)-1;

            return -dividend;
        }

        bool minus = dividend < 0 != divisor < 0;
        dividend = abs(dividend);
        divisor = abs(divisor);
#if 1
        unsigned short i=0;
        for(; 1 < divisor>>i; ++i) {

//            LOGV(i);
//            LOGV(divisor>>i);
        }

        return dividend>>i;
#else
        int quotient = 0;
        int rest = dividend;
        while(rest > 0) {

            unsigned short i=0;
            for(; divisor>>(i+1) == 1; ++i);
            LOGV(i);
            rest = rest - (rest>>i);
        }
        return ;
#endif
    }
};


int main()
{
    LOGV(37/7);
    LOGV(Solution().divide(37, 7));
    return 0;

    int A=34;
    for(int i=0; i<A; ++i) {

        LOGV(i);
        LOGV(A>>i);
        LOGV(A/(1<<i));
    }

    return 0;

    int dividend = -(1L<<31);
    int divisor = -1;

    dividend = 34;
    divisor = 6;

    LOGV((1L<<31)-1);
    for(int i=1; i<=dividend; ++i) {

        LOGV("===========");
        divisor = i;
        LOGV(dividend);
        LOGV(divisor);
        LOGV(dividend/divisor);
        LOGV(Solution().divide(dividend, divisor));
    }

    return 0;
}
