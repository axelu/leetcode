
// 1680. Concatenation of Consecutive Binary Numbers
// https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/
// day 27 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/582/week-4-january-22nd-january-28th/3618/


// this approach passed all tests and the time limit when submitted
// when this became a daily challenge however, it failed the time limit
/*
class Solution {
private:
    string dp[100001];
public:
    int concatenatedBinary(int n) {
        dp[1] = "1";
        string r = "1";
        char ch;
        for(int i = 2; i <= n; ++i) {
            ch = (i % 2) + '0';
            dp[i] = dp[i/2] + ch;
            r += dp[i];
        }

        int MOD = 1000000007;
        int ans = 0;

        size_t l = r.size();
        for(int i = 0; i < l; ++i)
            ans = (ans % MOD * 2) % MOD + (r[i] == '1' ? 1 : 0);

        return ans;
    }
};
*/

// Solution Approach #3
class Solution {
public:
    int concatenatedBinary(int n) {
        const int MOD = 1000000007;
        int length = 0;   // bit length of addends
        long result = 0;  // long accumulator
        for (int i = 1; i <= n; i++) {
            // when meets power of 2, increase the bit length
            if ((i & (i - 1)) == 0) {
                length++;
            }
            result = ((result << length) | i) % MOD;
        }
        return result;
    }
};
