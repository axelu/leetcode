
// 1771. Maximize Palindrome Length From Subsequences
// https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/







// see 516. Longest Palindromic Subsequence
//     https://leetcode.com/problems/longest-palindromic-subsequence/

class Solution {
public:
    int longestPalindrome(string word1, string word2) {

        int n1 = word1.size();

        string s = word1 + word2;
        size_t n = s.size();

        int mx = 0;

        int dp[n][n];
        // string of size 1 is a palindrome with length 1
        for (int i = 0; i < n; ++i)
            dp[i][i] = 1;

        // sliding over string with length 2 to n
        for(int l = 2; l <= n; ++l)
            for(int b = 0; b < n-l+1; ++b) {
                int e = b+l-1;
                if( s[b] == s[e] && l == 2) {
                    dp[b][e] = 2;
                    if( b < n1 && e >= n1 )
                        mx = max(mx,dp[b][e]);

                } else if( s[b] == s[e] ) {
                    dp[b][e] = dp[b+1][e-1] + 2;
                    if( b < n1 && e >= n1 )
                        mx = max(mx,dp[b][e]);

                } else {
                    dp[b][e] = max(dp[b][e-1], dp[b+1][e]);
                    /*
                    if( b < n1 && e-1 >= n1 )
                        mx = max(mx,dp[b][e-1]);
                    if( b+1 < n1 && e >= n1 )
                        mx = max(mx,dp[b+1][e]);
                    */
                }
            }

        return mx <= 1 ? 0 : mx;

    }
};
