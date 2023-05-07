
// 2414. Length of the Longest Alphabetical Continuous Substring
// https://leetcode.com/problems/length-of-the-longest-alphabetical-continuous-substring/




class Solution {
public:
    int longestContinuousSubstring(string s) {
        int n = s.size();
        if( n == 1 )
            return 1;

        int ans = 1;
        int t = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i-1] + 1 == s[i] ) {
                ++t;
            } else {
                ans = max(ans,t);
                t = 1;
            }
        }
        ans = max(ans,t);

        return ans;
    }
};
