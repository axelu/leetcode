
// 334. Increasing Triplet Subsequence
// https://leetcode.com/problems/increasing-triplet-subsequence/
// day 18 Decemeber 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/571/week-3-december-15th-december-21st/3570/


// see 300. Longest Increasing Subsequence
// https://leetcode.com/problems/longest-increasing-subsequence/
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        size_t n = nums.size();
        if( n < 3 ) return false;
        if( n == 3 ) return nums[0] < nums[1] && nums[1] < nums[2];

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
            if( llis == 3 ) return true;
        }
        return false;
   }
};
