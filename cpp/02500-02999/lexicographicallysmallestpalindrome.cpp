
// 2697. Lexicographically Smallest Palindrome
// https://leetcode.com/problems/lexicographically-smallest-palindrome/



class Solution {
public:
    string makeSmallestPalindrome(string s) {
        int n = s.size();

        int i = 0;      // left index
        int j = n-1;    // right index
        while( i < j ) {

            if( s[i] < s[j] ) {
                s[j] = s[i];
            } else if( s[j] < s[i] ) {
                s[i] = s[j];
            }

            ++i;
            --j;
        }

        return s;
    }
};
