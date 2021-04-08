
// 1641. Count Sorted Vowel Strings
// https://leetcode.com/problems/count-sorted-vowel-strings/




class Solution {
private:
    int dp[51][5];

    int count(int n, int last_char) {
        if( n == 0 ) return 1;

        if( dp[n][last_char] != -1 ) return dp[n][last_char];

        int r = 0;
        for(int i = 0; i < 5; ++i)
            if( i >= last_char )
                r += count(n-1,i);

        return dp[n][last_char] = r;
    }
public:
    int countVowelStrings(int n) {
        // init dp
        for(int i = 0; i < 51; ++i)
            for(int j = 0; j < 5; ++j)
                dp[i][j] = -1;

        return count(n,0);
    }
};
