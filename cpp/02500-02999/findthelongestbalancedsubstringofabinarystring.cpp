
// 2609. Find the Longest Balanced Substring of a Binary String
// https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/




class Solution {
public:
    int findTheLongestBalancedSubstring(string s) {
        int n = s.size();

        int ans = 0;

        int zeros = 0;
        int ones  = 0;
        for(int i = 0; i < n; ++i) {

            if( s[i] == '0' ) {
                if( i > 0 && s[i-1] == '1' ) {
                    zeros = 0;
                    ones  = 0;
                }
                ++zeros;

            } else {
                ++ones;
                ans = max(ans, min(zeros,ones) * 2);
            }
        }

        return ans;
    }
};
