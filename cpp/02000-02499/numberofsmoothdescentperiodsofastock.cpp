
// 2110. Number of Smooth Descent Periods of a Stock
// https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/


class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {

        int pre = -1;
        long long cnt = -1;

        long long ans = 0;

        int n = prices.size();
        for(int i = 0; i < n; ++i) {
            if( pre - prices[i] == 1 )
                ++cnt;
            else
                cnt = 1;

            ans += cnt;
            pre = prices[i];
        }

        return ans;
    }
};
