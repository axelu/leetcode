
// 1221. Split a String in Balanced Strings
// https://leetcode.com/problems/split-a-string-in-balanced-strings/


class Solution {
public:
    int balancedStringSplit(string s) {
        int balance = 0;
        int r = 0;
        for(auto it = begin(s); it != end(s); ++it) {
            balance = *it == 'L' ? balance + 1 : balance - 1;
            if( balance == 0 ) ++r;
        }

        return r;
    }
};
