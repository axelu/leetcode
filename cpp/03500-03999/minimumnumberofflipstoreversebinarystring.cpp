
// 3750. Minimum Number of Flips to Reverse Binary String
// https://leetcode.com/problems/minimum-number-of-flips-to-reverse-binary-string/



class Solution {
public:
    int minimumFlips(int n) {

        string s_rev = "";
        while( n ) {
            if( n & 1 )
                s_rev.push_back('1');
            else
                s_rev.push_back('0');
            n >>= 1;
        }
        string s = s_rev;
        reverse(begin(s_rev), end(s_rev));

        int ans = 0;
        for(int i = 0; i < s.size(); ++i)
            if( s[i] != s_rev[i] )
                ++ans;

        return ans;
    }
};
