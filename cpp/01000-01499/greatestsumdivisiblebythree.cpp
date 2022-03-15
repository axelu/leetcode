
// 1262. Greatest Sum Divisible by Three
// https://leetcode.com/problems/greatest-sum-divisible-by-three/



class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0] % 3 == 0 ? nums[0] : 0;

        // dp[pos][mod] max sum starting at pos where current sum modulo 3 is equal to mod
        int dp[n][3];
        dp[n-1][0] = 0;
        dp[n-1][1] = 0;
        dp[n-1][2] = 0;
        dp[n-1][nums[n-1]%3] = nums[n-1];

        for(int pos = n-2; pos >= 0; --pos) {
            int m = nums[pos] % 3;
            if( m == 0 ) {
                dp[pos][0] = nums[pos] + dp[pos+1][0];
                dp[pos][1] = dp[pos+1][1] > 0 ? nums[pos] + dp[pos+1][1] : 0;
                dp[pos][2] = dp[pos+1][2] > 0 ? nums[pos] + dp[pos+1][2] : 0;
            } else if( m == 1 ) {
                dp[pos][0] = dp[pos+1][2] > 0 ? max(dp[pos+1][0], nums[pos] + dp[pos+1][2]) : dp[pos+1][0];
                dp[pos][1] = max(dp[pos+1][1], nums[pos] + dp[pos+1][0]);
                dp[pos][2] = dp[pos+1][1] > 0 ? max(dp[pos+1][2], nums[pos] + dp[pos+1][1]) : dp[pos+1][2];
            } else {
                dp[pos][0] = dp[pos+1][1] > 0 ? max(dp[pos+1][0], nums[pos] + dp[pos+1][1]) : dp[pos+1][0];
                dp[pos][1] = dp[pos+1][2] > 0 ? max(dp[pos+1][1], nums[pos] + dp[pos+1][2]) : dp[pos+1][1];
                dp[pos][2] = max(dp[pos+1][2], nums[pos] + dp[pos+1][0]);
            }
        }

        return dp[0][0];
    }
};
