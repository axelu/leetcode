
// 1137. N-th Tribonacci Number
// https://leetcode.com/problems/n-th-tribonacci-number/



class Solution {
public:
    int tribonacci(int n) {
        // 0 <= n <= 37
        // hence answer is guaranteed to fit within a 32-bit integer, answer <= 2^31 - 1

        if( n == 0 ) return 0;
        else if( n == 1 || n == 2 ) return 1;

        int dp[n+1];
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for(int i = 3; i <= n; ++i)
            dp[i] = dp[i-3] + dp[i-2] + dp[i-1];

        return dp[n];
    }
};
