
// 1092. Shortest Common Supersequence 
// https://leetcode.com/problems/shortest-common-supersequence/


class Solution {
private:
    // see 1143. Longest Common Subsequence
    // https://leetcode.com/problems/longest-common-subsequence/

    int dp[1001][1001];

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

    int longestCommonSubsequence(string& text1, string& text2) {
        size_t n1 = text1.size();
        size_t n2 = text2.size();

        memset(dp,-1,sizeof dp);
        // top down
        return td(text1,text2,n1,n2);
    }

public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n1 = str1.size();
        int n2 = str2.size();

        longestCommonSubsequence(str1,str2);

        string ans = "";

        // if we move through str1 and str2 while maintaining
        // the longest common subsequence, it will result in
        // shortest common supersequence, if we take every common char
        int i = n1; // str1
        int j = n2; // str2
        while( i > 0 & j > 0 )
           if( str1[i-1] == str2[j-1] ) {
                ans = str1[i-1] + ans;
                --i;
                --j;
            } else if( dp[i][j-1] > dp[i-1][j] ) {
				ans = str2[j-1] + ans;
				--j;
			} else {
				    ans = str1[i-1] + ans;
				    --i;
            }

        for(;i > 0; --i)
           ans = str1[i-1] + ans;
        for(;j > 0; --j )
            ans = str2[j-1] + ans;

        return ans;
     }
};
