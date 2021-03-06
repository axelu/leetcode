
// 509. Fibonacci Number
// https://leetcode.com/problems/fibonacci-number/


class Solution {
public:
    int fib(int N) {
        // 0 ≤ N ≤ 30, hence answer will fit into 32-bit integer, answer < 2^31 - 1

        if( N == 0 ) return 0;
        else if( N == 1 ) return 1;

        int dp[N+1];
        dp[0] = 0;
        dp[1] = 1;

        for(int i = 2; i <= N; ++i)
           dp[i] = dp[i-2] + dp[i-1];

        return dp[N];
    }
};
