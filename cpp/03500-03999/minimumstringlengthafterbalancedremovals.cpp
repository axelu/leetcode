
// 3746. Minimum String Length After Balanced Removals
// https://leetcode.com/problems/minimum-string-length-after-balanced-removals/description/

class Solution {
private:

public:
    int minLengthAfterRemovals(string s) {
        int n = s.size(); // 1 <= n <= 1e5; s[i] is either 'a' or 'b'
        if( n == 1 )
            return 1;
        if( n == 2 )
            return s[0] != s[1] ? 0 : 2;
        if( n == 2 )
            return s[0] != s[1] || s[1] != s[2] ? 1 : 3;

        vector<int> prefixSum(n+1); // default 0
        for(int i = 1; i <= n; ++i) {
            int addend = s[i-1] == 'a' ? 1 : -1;
            prefixSum[i] = prefixSum[i-1] + addend;
        }
        if( prefixSum[n] == 0 )
            return 0;


        vector<int> dp(n+1);
        vector<int> um(2*n+1,-1);
        um[prefixSum[n]+n] = n;
        for(int i = n-1; i >= 0; --i) {
            int ps = prefixSum[i];

            // prefixSum[j] == ps where j > i
            // we can eleminate all elements i..j-1
            // we would continue at j
            // so we are looking for the max of
            // (j-i) + ans[j] for every j
            // we only need to check the furthest out

            dp[i] = dp[i+1]; // skip
            if( um[ps+n] != -1 )
                dp[i] = max(dp[i], (um[ps+n]-i) + dp[um[ps+n]]);
            else 
                um[ps+n] = i;
        }

        return n - dp[0];
    }
};
