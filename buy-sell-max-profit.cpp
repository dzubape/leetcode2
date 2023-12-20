#ifdef __SOLUTION_DEV
#define LOGGER_NAME LOG
#include "Solution.hpp"
#else
#define buySellMaxProfit maxProfit
#define LOGV(VALUE)
class Solution {
public:
    int maxProfit(std::vector<int>&);

};
#endif

int Solution::buySellMaxProfit(std::vector<int>& prices) {

#ifdef __SOLUTION_DEV
    constexpr const int INT_MAX = (1L<<31)-1;
    constexpr const int INT_MIN = -(1L<<31);
#endif

    int maxProfit = 0;

    int buyPrice = INT_MAX;
    int sellPrice = INT_MIN;

    typedef uint32_t SIZE_t;
    for(SIZE_t i=0; i<prices.size(); ++i) {

        if(prices[i] < buyPrice) {

            buyPrice = sellPrice = prices[i];
        }
        else if(prices[i] > sellPrice) {

            sellPrice = prices[i];
            prices[i] -= buyPrice;

            if(prices[i] > maxProfit) {

                maxProfit = prices[i];
            }
        }
    }

    LOGV(maxProfit);
    return maxProfit;
}

#include <iostream>

int Solution::test_buySellMaxProfit() {

    std::vector<int> testData = {1, 2, 3, 4, 3, 4, 5, 5};

    std::ifstream fs("../test_input.json");
    auto data = json::parse(fs);
    testData = data.get<std::vector<int>>();
    LOGV(data.size());
    int profit = buySellMaxProfit(testData);
    fs.close();
    return 0;
}

#if 0
// BEST SOLUTION //
int init = [] {
    cin.tie(nullptr)->sync_with_stdio(false);
    freopen("user.out", "w", stdout);

    for (string s; getline(cin, s); cout << '\n') {
        int solution = 0, minPrice = INT_MAX;
        for (int _i = 1, _n = s.length(); _i < _n; ++_i) {
            int price = s[_i++] & 15;
            while ((s[_i] & 15) < 10) price = price * 10 + (s[_i++] & 15);
            minPrice = min(minPrice, price);
            solution = max(solution, price - minPrice);
        }
        cout << solution;
    }
    exit(0);
    return 0;
}();

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        return 0;
    }
};
#endif
