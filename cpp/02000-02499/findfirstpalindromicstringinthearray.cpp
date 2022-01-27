
// 2108. Find First Palindromic String in the Array
// https://leetcode.com/problems/find-first-palindromic-string-in-the-array/




class Solution {
public:
    string firstPalindrome(vector<string>& words) {
        int b,e;
        bool f;
        for(string& s : words) {
            b = 0;
            e = s.size()-1;
            f = true;;
            while(b < e) {
                if (s[b] != s[e]) {
                    f = false;
                    break;
                }
                ++b;
                --e;
            }
            if( f )
                return s;
        }

        return "";
    }
};
