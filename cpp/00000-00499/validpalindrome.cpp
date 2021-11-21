
// 125. Valid Palindrome
// https://leetcode.com/problems/valid-palindrome/

class Solution {
public:
    bool isPalindrome(string s) {
        if ( s.empty() || s.size() == 1 ) return true;

        bool p = true;

        auto fi = s.begin();
        auto ri = s.rbegin();
        while( fi <= ri.base() && fi != s.end() ) {

            while (fi != s.end() ) {
                if ( isalnum(*fi) ) break;
                ++fi;
            }
            if ( fi != s.end() && fi <= ri.base() ) {
                while (ri != s.rend() ) {
                    if ( isalnum(*ri) ) break;
                    ++ri;
                }
                if ( tolower(*fi) == tolower(*ri) ) {
                    ++fi;
                    ++ri;
                } else {
                    p = false;
                    break;
                }
            }
        }

        return p;
    }
};
