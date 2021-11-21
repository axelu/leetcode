
// 1525. Number of Good Ways to Split a String
// https://leetcode.com/problems/number-of-good-ways-to-split-a-string/




class Solution {
public:
    int numSplits(string s) {
        int n = s.size();
        if( n == 1 ) return 0;
        if( n == 2 ) return 1;

        int cntFwd[26];
        int cntBwd[26];
        int i;

        memset(cntFwd,0,sizeof cntFwd);cntFwd[s[0]  -'a'] = 1;
        memset(cntBwd,0,sizeof cntBwd);cntBwd[s[n-1]-'a'] = 1;

        int fwd[n];fwd[0]   = 1;
        int bwd[n];bwd[n-1] = 1;

        int ans = 0;

        for(i = 1; i < n-1; ++i) {
            // forward
            if( cntFwd[s[i]-'a'] == 0 ) {
                fwd[i] = fwd[i-1] + 1;
                cntFwd[s[i]-'a'] = 1;
            } else {
                fwd[i] = fwd[i-1];
            }
            // backward
             if( cntBwd[s[n-1-i]-'a'] == 0 ) {
                bwd[n-1-i] = bwd[n-i] + 1;
                cntBwd[s[n-1-i]-'a'] = 1;
            } else {
                bwd[n-1-i] = bwd[n-i];
            }

            // count when left index (i) and right index (n-1-i) cross
            if( (n-1-i) - i == 1 ) {
                if( fwd[i] == bwd[i+1] ) ++ans;
            } else if( (n-1-i) - i <= 1) {
                if( fwd[i] == bwd[i+1] ) ++ans;
                if( bwd[n-1-i] == fwd[n-2-i] ) ++ans;
            }

        }

        return ans;
    }
};
