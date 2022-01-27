
// 696. Count Binary Substrings
// https://leetcode.com/problems/count-binary-substrings/


class Solution {
public:
    int countBinarySubstrings(string s) {
        int n = s.size();
        if( n == 1 ) return 0;

        int ans = 0;
        int zeros = 0, ones = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                if( i > 0 && s[i-1] == '1' )
                    zeros = 0;
                ++zeros;
                if( ones > 0 ) {
                    ++ans;
                    --ones;
                }
            } else {
                if( i > 0 && s[i-1] == '0' )
                    ones = 0;
                ++ones;
                if( zeros > 0 ) {
                    ++ans;
                    --zeros;
                }
            }
        }
        return ans;
    }
};
