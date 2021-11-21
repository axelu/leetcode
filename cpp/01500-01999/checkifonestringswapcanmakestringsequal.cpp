
// 1790. Check if One String Swap Can Make Strings Equal
// https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/


class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int n = s1.size(); // 1 <= s1.length, s2.length <= 100

        int d = 0, l = -1, r = -1;
        for(int i = 0; i < n; ++i) {
            if( s1[i] != s2[i] ) ++d;
            if( d == 1 && l == -1 ) l = i;
            else if( d == 2 && r == -1 ) r = i;
            if( d > 2 ) return false;
        }
        if( d == 0 ) return true;
        if( d != 2 ) return false;

        return s1[r] == s2[l] && s1[l] == s2[r];
    }
};
