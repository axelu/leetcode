
// 121. Best Time to Buy and Sell Stock
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = INT_MAX; // init to a max, as we want a minimum
        int profit = 0;

        for (auto it = prices.begin(); it != prices.end(); ++it) {
            buy = min(buy, *it);
            profit = max(profit, *it - buy);
        }

        return profit;
    }
};
