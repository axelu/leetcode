
// 2830. Maximize the Profit as the Salesman
// https://leetcode.com/problems/maximize-the-profit-as-the-salesman/




class Solution {
public:
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {
        // offers[i] = [starti, endi, goldi]
        vector<int> offersByStart[n];
        int offers_sz = offers.size();
        for(int i = 0; i < offers_sz; ++i)
            offersByStart[offers[i][0]].push_back(i);

        int dp[n+1];
        dp[n] = 0;
        for(int i = n-1; i >= 0; --i) {
            dp[i] = dp[i+1];
            for(int j: offersByStart[i])
                dp[i] = max(dp[i], offers[j][2] + dp[offers[j][1]+1]);
        }

        return dp[0];
    }
};
