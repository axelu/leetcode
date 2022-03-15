
// 1682. Longest Palindromic Subsequence II
// https://leetcode.com/problems/longest-palindromic-subsequence-ii/




class Solution {
public:
    int longestPalindromeSubseq(string& s) {
        int n = s.size();

        /* good palindrome:
         *     It is a subsequence of s.
         *     It is a palindrome (has the same value if reversed).
         *     It has an even length.
         *     No two consecutive characters are equal, except the two middle ones.
         */

        int dp[n][n][26];memset(dp,0,sizeof dp);

        // sliding over string with length 2 to n
        for(int l = 2; l <= n; ++l)
            for(int b = 0; b < n-l+1; ++b) {
                int e = b+l-1;
                if( s[b] == s[e] && l == 2) {
                    dp[b][e][s[b]-'a'] = 2;
                } else if( s[b] == s[e] ) {
                    int t = 0;
                    for(int i = 0; i < 26; ++i)
                        if( i != s[b] - 'a' )
                            t = max(t,dp[b+1][e-1][i]);
                    dp[b][e][s[b]-'a'] = max(t + 2, dp[b+1][e-1][s[b]-'a']);
                } else {
                    for(int i = 0; i < 26; ++i)
                        dp[b][e][i] = max(dp[b][e-1][i],dp[b+1][e][i]);
                }
            }

        int ans = 0;
        for(int i = 0; i < 26; ++i)
            ans = max(ans,dp[0][n-1][i]);

        return ans;
    }
};
