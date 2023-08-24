#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define LOGV(VALUE)
class Solution {
public:
    int maxProfit(std::vector<int>&);

};
#endif

int Solution::maxProfit(std::vector<int>& prices) {

    constexpr const int _INT_MAX = (1L<<31)-1;
    constexpr const int _INT_MIN = -(1L<<31);

    LOGV(_INT_MAX);
    LOGV(_INT_MIN);

    int maxProfit = 0;

    int buyPrice = _INT_MAX;
    int sellPrice = _INT_MIN;

    for(size_t i=0; i<prices.size(); ++i) {

        int price = prices[i];

        if(price < buyPrice) {

            buyPrice = price;
            sellPrice = price;
        }
        else if(price > sellPrice) {

            sellPrice = price;

            if(sellPrice - buyPrice > maxProfit) {

                maxProfit = sellPrice - buyPrice;
            }
        }
    }

    LOGV(maxProfit);
    return maxProfit;
}

#include <iostream>

int Solution::test_maxProfit() {

    std::vector<int> testData = {1, 2, 3, 4, 3, 4, 5, 5};

    std::ifstream fs("../test_input.json");
    auto data = json::parse(fs);
    testData = data.get<std::vector<int>>();
//    LOGV(data);
    int profit = maxProfit(testData);
    fs.close();
    return 0;
}
