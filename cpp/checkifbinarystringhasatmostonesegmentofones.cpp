
// 1784. Check if Binary String Has at Most One Segment of Ones
// https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/



class Solution {
public:
    bool checkOnesSegment(string s) {
        int n = s.size();

        for(int i = 1; i < n; ++i)
            if( s[i] == '1' && s[i-1] == '0' ) return false;

        return true;
    }
};
