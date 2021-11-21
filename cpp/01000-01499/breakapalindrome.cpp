
// 1328. Break a Palindrome
// https://leetcode.com/problems/break-a-palindrome/



class Solution {
public:
    string breakPalindrome(string& p) {
        int n = p.size();
        if( n == 1 ) return "";

        if( n == 2 ) {
            if( p[0] != 'a' ) p[0] = 'a';
            else p[1] = 'b';
            return p;
        }

        for(int i = 0; i < n/2; ++i) {
            // change 1st char that is different than a to a
            if( p[i] != 'a' ) {
                p[i] = 'a';
                return p;
            }
        }
        // if we are still here it can only be the last letter
        p[n-1] = 'b';
        return p;
    }
};
