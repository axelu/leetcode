
// 940. Distinct Subsequences II
// https://leetcode.com/problems/distinct-subsequences-ii/



// based on solution apprach #1
class Solution {
public:
    int distinctSubseqII(string s) {
        int n = s.size();
        long mod = 1000000007;

        long dp[n+1];
        dp[0] = 1;
        // remember at which index a given char was seen last
        int last_seen[26];memset(last_seen,-1,sizeof last_seen);

        for(int i = 0; i < n; ++i){
            int c = s[i] - 'a';
            dp[i+1] = (dp[i] * 2) % mod;

            // the last time we have seen the same char
            // that number must be subtracted to avoid double counting
            if( last_seen[c] >= 0 )
                dp[i+1] = dp[i+1] - dp[last_seen[c]];

            if( dp[i+1] < 0 )
                    dp[i+1] += mod;

            last_seen[c] = i;
        }

        dp[n]--; // subtract empty subsequence

        return dp[n];
    }
};
