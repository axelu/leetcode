
// 2370. Longest Ideal Subsequence
// https://leetcode.com/problems/longest-ideal-subsequence/




class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        if( n == 1 )
            return 1;

        int dp[26];memset(dp,0,sizeof dp);
        for(int i = n-1; i >= 0; --i) {
            int chr = s[i]-'a';

            // on the low end we can connect to chr-k inclusive
            // on the high end we can connect to chr+k inclusive

            int s = max(0,chr-k);
            int e = min(25,chr+k);
            int l = 0;
            for(int j = s; j <= e; ++j)
                l = max(l,dp[j]);

            dp[chr] = 1 + l;
        }

        int ans = 0;
        for(int i = 0; i < 26; ++i)
            ans = max(ans,dp[i]);

        return ans;
    }
};
