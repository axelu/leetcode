
// 2266. Count Number of Texts
// https://leetcode.com/problems/count-number-of-texts/


class Solution {
public:
    int countTexts(string& pressedKeys) {
        int n = pressedKeys.size();

        long mod = 1000000007;

        // bottom up
        long dp[n+1];
        dp[n-1] = dp[n] = 1;
        // for key 7 and 9 we can go back 4, all others 3
        for(int i = n-2; i >= 0; --i) {
            dp[i] = dp[i+1];
            if( pressedKeys[i] == pressedKeys[i+1] ) {
                dp[i] = (dp[i] + dp[i+2]) % mod;

                if( i <= n-3 && pressedKeys[i] == pressedKeys[i+2] ) {
                    dp[i] = (dp[i] + dp[i+3]) % mod;

                    if( (pressedKeys[i] == '7' || pressedKeys[i] == '9') &
                        i <= n-4 && pressedKeys[i] == pressedKeys[i+3] )
                        dp[i] = (dp[i] + dp[i+4]) % mod;
                }
            }
        }

        return dp[0];
    }
};
