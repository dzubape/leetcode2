#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE) ()
class Solution {
public:
    int maxProfit(std::vector<int>&);

};
#endif

int Solution::maxProfit(std::vector<int>& prices) {

    constexpr const int INT_MAX = (1L<<31)-1;
    constexpr const int INT_MIN = -(1L<<31);

    LOGV(INT_MAX);
    LOGV(INT_MIN);

//    struct {
//        int value;
//        size_t idx;
//    } minPrice{INT_MAX, prices.size()}, maxPrice{INT_MIN, prices.size()};

    int maxProfit = 0;

    for(size_t i=0; i<prices.size()-1; ++i) {

        auto buyPrice = prices[i];

        for(size_t j=i+1; j<prices.size(); ++j) {

            int sellPrice = prices[j];

            if(sellPrice - buyPrice > maxProfit) {

                maxProfit = sellPrice - buyPrice;
            }
        }
    }

//#define MAX(A, B) (A > B ? A : B)
    LOGV(maxProfit);
    return maxProfit;
}

int Solution::test_maxProfit() {

    std::vector<int> testData = {1, 2, 3, 4, 3, 4, 5, 5};
    return maxProfit(testData);
}
