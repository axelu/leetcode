
// 3773. Maximum Number of Equal Length Runs
// https://leetcode.com/problems/maximum-number-of-equal-length-runs/



class Solution {
public:
    int maxSameLengthRuns(string s) {
        int n = s.size();
        if( n == 1 )
            return 1;

        unordered_map<int,int> runsbylen; // key: run length; value: count

        int len = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i] != s[i-1] ) {
                // a run ends;
                ++runsbylen[len];
                len = 1;
                continue;
            }
            ++len;
        }
        // finish up
        ++runsbylen[len];

        int ans = 0;
        for(auto& p: runsbylen)
            ans = max(ans, p.second);

        return ans;
    }
};
