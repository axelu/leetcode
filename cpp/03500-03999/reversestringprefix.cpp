
// 3794. Reverse String Prefix
// https://leetcode.com/problems/reverse-string-prefix/


class Solution {
public:
    string reversePrefix(string s, int k) {
        auto it = s.begin();
        it += k;
        reverse(s.begin(), it);
        return s;
    }
};
