
// 1216. Valid Palindrome III
// https://leetcode.com/problems/valid-palindrome-iii/






// see
// 516. Longest Palindromic Subsequence
// https://leetcode.com/problems/longest-palindromic-subsequence/


class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.size();

        int dp[n][n];
        // string of size 1 is a palindrome with length 1
        for (int i = 0; i < n; ++i)
            dp[i][i] = 1;

        // sliding over string with length 2 to n
        for(int l = 2; l <= n; ++l)
            for(int b = 0; b < n-l+1; ++b) {
                int e = b+l-1;
                if( s[b] == s[e] && l == 2)
                    dp[b][e] = 2;
                else if( s[b] == s[e] )
                    dp[b][e] = dp[b+1][e-1] + 2;
                else
                    dp[b][e] = max(dp[b][e-1], dp[b+1][e]);
            }


        return dp[0][n-1] >= n-k;
    }
};
