
// 1714. Sum Of Special Evenly-Spaced Elements In Array
// https://leetcode.com/problems/sum-of-special-evenly-spaced-elements-in-array/




class Solution {
private:
    long mod = 1000000007;
    int n;
    int * _nums;

    int bf(int x, int y) {
        long ret = 0;
        while( x < n ) {
            ret = (ret + _nums[x]) % mod;
            x += y;
        }
        return ret;
    }

public:
    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        n = nums.size();
        _nums = nums.data();

        // precalc answer for y's smaller than sqrt(n)
        int n_sqrt = sqrt(n);   // max n = 50000 -> sqrt(50000) = 223
        // long dp[50000][223];
        long dp[n][n_sqrt];

        for(int i = n-1; i >= 0; --i) {
            for(int y = 1; y < n_sqrt; ++y) {
                dp[i][y] = nums[i];
                if( i + y < n )
                    dp[i][y] = (dp[i][y] + dp[i+y][y]) % mod;
            }
        }

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int x = queries[i][0];
            int y = queries[i][1];

            if( y >= n_sqrt ) {
                // brute force
                ans[i] = bf(x,y);
            } else {
                ans[i] = dp[x][y];
            }
        }

        return ans;
    }
};
