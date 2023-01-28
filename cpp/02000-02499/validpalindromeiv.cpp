
// 2330. Valid Palindrome IV
// https://leetcode.com/problems/valid-palindrome-iv/



class Solution {
public:
    bool makePalindrome(string& s) {
        int d = 0;
        auto fi = s.begin();
        auto ri = s.rbegin();
        while( fi < ri.base() ) {
            if( *fi != *ri ) {
                ++d;
                if( d > 2)
                    break;
            }
            ++fi;
            ++ri;
        }

        return d <= 2;
    }
};
