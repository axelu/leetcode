
// 1027. Longest Arithmetic Subsequence
// https://leetcode.com/problems/longest-arithmetic-subsequence/




class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();

        // for each arithmetic sequence ending at i, find the longest arithmetic sequence
        // ending at j (where i > j) with difference d = nums[i] - nums[j]

        // our solution space, meaning our possible differences, is [-500,500]
        int dp[n][1001];memset(dp,0,sizeof dp);
        int o = 500; // offset

        int ans = 0;

        int diff;
        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                diff = nums[i]-nums[j];
                if( dp[j][diff+o] == 0 )
                    dp[i][diff+o] = 2;
                else
                    dp[i][diff+o] = max(dp[i][diff+o],dp[j][diff+o]+1);

                // keeping track of longest arithmetic sequence ever seen
                ans = max(ans,dp[i][diff+o]);
           }
        }

        return ans;
    }
};
