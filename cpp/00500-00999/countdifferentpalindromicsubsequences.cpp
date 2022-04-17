
// 730. Count Different Palindromic Subsequences
// https://leetcode.com/problems/count-different-palindromic-subsequences/



class Solution {
public:
    int countPalindromicSubsequences(string s) {
        int n = s.size();
        if( n == 1 )
            return 1;

        // if we have 2 chars, it does not matter if
        // s[0] == s[i] or s[0] != s[1]
        // e.g. ab: we have 2 unique palindromic subsequences: a,b
        //      aa: we have 2 unique palindromic subsequences: a,aa
        if( n == 2 )
            return 2;

        // if we have 3 or more chars, then it depends
        // s[i] s[i+1,j-1] s[j] -> begin middle end
        // if s[i] != s[j], then the answer is
        //     ans[i,j-1] + ans[i+1,j] - ans[i+1,j-1]
        // if s[i] == s[j], then the answer depends on
        // how many times 0,1 or more char at i occurs between i and j
        // in order to determine that, we need to know the
        // next occurence of char at i to its right respectively
        // the next occurence of char at j to its left (aka previous occurence)

        int f[4];memset(f,-1,sizeof f); // last occurence of a,b,c and d

        int next[n];
        for(int i = n - 1; i >= 0; --i) { // going right to left
            int c = s[i]-'a';
            if( f[c] != -1 )
                next[i] = f[c];
            else
                next[i] = -1;
            f[c] = i;
        }

        memset(f,-1,sizeof f);
        int prev[n];
        for(int i = 0; i < n; ++i) {
            int c = s[i]-'a';
            if( f[c] != -1 )
                prev[i] = f[c];
            else
                prev[i] = -1;
            f[c] = i;
        }

        long mod = 1000000007;

        long dp[n][n];memset(dp,0,sizeof dp); // memset should not be needed
        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;
        for(int i = 0; i < n-1; ++i)
            dp[i][i+1] = 2;

        // slide a window of length l over s
        int i,j;
        for(int l = 3; l <= n; ++l) {
            for(i = 0, j = i+l-1; j < n; ++i, ++j) {
                if( s[i] != s[j] ) {
                    dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]) % mod;
                    // as we are doing modulo, it could become negative
                    if( dp[i][j] < 0 )
                        dp[i][j] += mod;

                } else {
                    // starting from i, where is the next occurence of the char at i
                    int nxt = next[i];
                    // starting from j, where is the prev occurence of the char at j
                    int pre = prev[j];

                    if( nxt == pre ) {
                        // there is exactly one occurence of the char at i respectively char at j
                        // between i and j
                        // each palindromic subsequence between i and j can be surrounded by the
                        // char at i and j giving us 2 times more of those, which includes the
                        // one occurence of our char, so like a___a________a
                        // the one additional subsequence we are picking up is aa
                        dp[i][j] = (2 * dp[i+1][j-1] + 1) % mod;

                    } else if( nxt < pre ) {
                        // there are multiple occurences of the char at i respectively char at j
                        // between i and j, so like a_____a________a____a
                        //                               nxt      pre
                        // by surrounding the palindromic subsequences between nxt and prev with the
                        // same char, we are not gaining anything
                        dp[i][j] =((2 * dp[i+1][j-1]) % mod) - dp[nxt+1][pre-1];
                        // as we are doing modulo, it could become negative
                        if( dp[i][j] < 0 )
                            dp[i][j] += mod;

                    } else {
                        // there is no occurence of the char at i respectively char at j
                        // between i and j
                        // each palindromic subsequence between i and j can be surrounded by the
                        // char at i and j giving us 2 times more of those, and we are picking up
                        // like a,aa if the char at i respectively j is a; or b,bb if b, etc.
                        dp[i][j] = (2 * dp[i+1][j-1] + 2) % mod;
                    }
                }
            }
        }


        return dp[0][n-1];
    }
};
