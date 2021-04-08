
// 72. Edit Distance
// https://leetcode.com/problems/edit-distance/



// see https://www.geeksforgeeks.org/edit-distance-dp-using-memoization/
class Solution {
private:
    int dp[500][500];

    int minDistance(string& word1, string& word2, int m, int n) {
        // first string is empty
        // insert all chars from second string into first
        if( m == 0 )
            return n;

        // second string is empty
        // remove all characters of first string
        if( n == 0 )
            return m;

        if( dp[m-1][n-1] != -1 )
            return dp[m-1][n-1];

        int ans;

        // if last char of two strings are same, do nothing
        // ignore last char and get count for remaining strings
        if( word1[m-1] == word2[n-1] )
            ans = minDistance(word1,word2,m-1,n-1);

        // if last char of two strings are not same,
        // consider all three possible operations (insert,remove,replace)
        // on last character of first string
        else
            ans = 1 + min({minDistance(word1,word2,m,n-1),     // insert
                           minDistance(word1,word2,m-1,n),     // remove
                           minDistance(word1,word2,m-1,n-1)}); // replace

        return dp[m-1][n-1] = ans;
    }

public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        memset(dp,-1,sizeof dp);
        return minDistance(word1,word2,m,n);
    }
};
