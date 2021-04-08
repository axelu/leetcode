
// 434. Number of Segments in a String
// https://leetcode.com/problems/number-of-segments-in-a-string/




class Solution {
public:
    int countSegments(string s) {
        int n = s.size();
        int ans = 0;

        for(int i = 0; i < n; ++i) {
            if( i == 0 && s[i] == ' ' ) {
                // don't do anything
            } else if( i > 0 && s[i] == ' ' && s[i-1] != ' ' ) {
                ++ans;
            } else if( i > 0 && s[i] == ' ' && s[i-1] == ' ' ) {
                // don't do anything
            }
            if( i == n-1 && s[i] !=  ' ') {
                ++ans;
            }
        }

        return ans;

    }
};
