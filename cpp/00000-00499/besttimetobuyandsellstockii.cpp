
// 122. Best Time to Buy and Sell Stock II
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = INT_MAX; // init to a max, as we want a minimum
        int profit = INT_MIN;
        int total_profit = 0;

        for (auto it = prices.begin(); it != prices.end(); ++it) {
            if ( *it - buy < profit ) {
                // reset
                total_profit += profit;
                buy = INT_MAX;
                profit = INT_MIN;
            }
            buy = min(buy, *it);
            profit = max(profit, *it - buy);
        }
        // closing out if needed
        if ( *(prices.end()-1) - buy == profit ) total_profit += profit;

        return total_profit;
    }
};
