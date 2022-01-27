
// 680. Valid Palindrome II
// https://leetcode.com/problems/valid-palindrome-ii/



class Solution {
private:
    bool validPalindrome(string& s, int l, int r) {
        while(l<r) {
            if( s[l] != s[r] ) return false;
            ++l;
            --r;
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
        int n = s.size();
        if( n == 1 ) return true;

        int l = 0;
        int r = n-1;

        while(l<r) {
            if( s[l] != s[r] ) break;
            ++l;
            --r;
        }
        if( l == r || l > r ) return true;
        if( validPalindrome(s,l+1,r) ) return true;
        return validPalindrome(s,l,r-1);
    }
};
