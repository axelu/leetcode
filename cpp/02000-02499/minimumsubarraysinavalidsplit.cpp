
// 2464. Minimum Subarrays in a Valid Split
// https://leetcode.com/problems/minimum-subarrays-in-a-valid-split/



class Solution {
private:
    // greatest common denominator
    int gcd(int a, int b) {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }

public:
    int validSubarraySplit(vector<int>& nums) {
        int n = nums.size();
        if( nums[0] == 1 || nums[n-1] == 1 )
            return -1;
        if( n == 1 )
            return 1;

        // let dp[i] be the minimum number of subarrays that
        //     validly split [a[0], a[1], … , a[i - 1]]
        int dp[n+1];
        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2; i <= n; ++i) {
            // initially assume nums[i-1] needs to stand by itself
            // which is worst case
            int t = nums[i-1] == 1 ? 10000 : dp[i-1] + 1;
            // can we do better?
            for(int j = 0; j < i-1; ++j)
                if( gcd(nums[j],nums[i-1]) > 1 )
                    t = min(t,dp[j]+1);
            dp[i] = t;
        }

        /*
        if( dp[n] == n )
            for(int i = 0; i < n; ++i)
                if( nums[i] == 1 )
                    return -1;
        */

        return dp[n] >= 10000 ? -1 : dp[n];
    }
};
