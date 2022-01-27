
// 1414. Find the Minimum Number of Fibonacci Numbers Whose Sum Is K
// https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/



class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        // 1 <= k <= 10^9

        int N = 45;
        int dp[N+1];
        dp[0] = 0;
        dp[1] = 1;

        for(int i = 2; i <= N; ++i)
           dp[i] = dp[i-2] + dp[i-1];

        int ans = 0;
        while( k != 0 ) {

            int i = N;
            for(; i > 0; --i) {
               if( dp[i] <= k )
                   break;
            }
            ++ans;
            k -= dp[i];
        }

        return ans;
    }
};
