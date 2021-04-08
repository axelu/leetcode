
// 300. Longest Increasing Subsequence
// https://leetcode.com/problems/longest-increasing-subsequence/


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if( n == 0 ) return 0;

        // length of longest increasing subsequence encountered ending at idx i
        // init to length of 1 at every index as there is at least the element iteself
        int dp[n];
        for(int i = 0; i < n; ++i) dp[i] = 1;

        int llis = 1; // length of longest increasing subsequence encountered

        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                if( nums[i] > nums[j] ) {
                    // record length of longest increasing subsequence
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            llis = max(llis, dp[i]); // keep track of lis ever encountered
        }

        return llis;
    }
};
