
// 3652. Best Time to Buy and Sell Stock using Strategy
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/




class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size(); // 2 <= prices.size() == strategy.size() <= 1e5

        // what if we build a prefix sum applying the original strategy
        // we then build a sliding window, initially starting at 0
        // with length k, where the first k / 2 elements to 0 (hold) and
        // the last k / 2 elements to 1 (sell).
        // we calculate the profit by sliding window profit + the right
        // remaining part, which we have in O1 time from our prefix sum
        // then we slide the window accross, the profit of our window
        // changes due to changes of two positions only, and the left
        // and right profit we get from our prefix sum

        // let k = 6 it is guaranteed that 2 <= k and that k is even
        // 01234567890123456789
        //    ------            sliding window
        //    000111
        //     000111
        //       x  x           positions that change profit of sliding window
        // note that the 1st half of our window is always really 0 profits !!!

        long long prefixSum[100001];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long long)(strategy[i-1] * prices[i-1]);

        long long ans = prefixSum[n]; // original strategy
        long long window_profit = 0LL;
        int i = 0;                    // left index
        for(int j = 0; j < n; ++j) {  // right index

            // only second half of sliding window
            if( j >= k/2 )
                window_profit += (long long)(prices[j]);

            if( j - i + 1 == k ) {
                long long left = prefixSum[i];
                long long right = prefixSum[n] - prefixSum[j+1];

                ans = max(ans, left + window_profit + right);

                // we are removing i from our window
                // but that is hold, meaning no profit/loss anyway
                // what matters is the 1st position of the second half
                // of our window

                int first_pos_second_half = i + k/2;
                window_profit -= (long long)(prices[first_pos_second_half]);

                ++i;
            }
        }

        return ans;
    }
};
