
// 1143. Longest Common Subsequence
// https://leetcode.com/problems/longest-common-subsequence/

// https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
// https://www.youtube.com/watch?v=Qf5R-uYQRPk
class Solution {
private:
    int dp[1001][1001];
    
    // bottom up
    int bu(string& text1, string& text2, int n1, int n2) {
        for(int i = 0; i <= n1; ++i)
            for(int j = 0; j <= n2; ++j) {
                if( i == 0 || j == 0 )
                    dp[i][j] = 0;
                else if( text1[i-1] == text2[j-1] ) // last char's of text1 and text2
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        return dp[n1][n2];
    }

    // top down
    int td(string& text1, string& text2, int n1, int n2) {
        if( dp[n1][n2] != -1 ) return dp[n1][n2];
        int ans;
        if( n1 == 0 || n2 == 0 ) 
            ans = 0;
        else if( text1[n1-1] == text2[n2-1] ) // last char's of text1 and text2
            ans = td(text1,text2,n1-1,n2-1) + 1;
        else
            ans = max(td(text1,text2,n1-1,n2),td(text1,text2,n1,n2-1));
        
        return dp[n1][n2] = ans;
    }
    
public:
    int longestCommonSubsequence(string& text1, string& text2) {
        size_t n1 = text1.size();
        size_t n2 = text2.size();

        // bottom up
        // return bu(text1,text2,n1,n2);
        
        // top down
        for (int i = 0; i <= n1; ++i)
            for (int j = 0; j <= n2; ++j)
                dp[i][j] = -1;
        return td(text1,text2,n1,n2);
    }
};
