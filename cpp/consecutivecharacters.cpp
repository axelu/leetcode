
// Consecutive Characters
// https://leetcode.com/problems/consecutive-characters/


class Solution {
public:
    int maxPower(string s) {
        int n = s.size();
        int c = 1;
        int r = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i] != s[i-1] ) {
                c = 1; // reset
            } else {
                ++c;
                r = max(r,c);
            }
        }
        return r;
    }
};
