
// 2839. Check if Strings Can be Made Equal With Operations I
// https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/



/* j - i = 2

 */
class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        if( s1 == s2 )
            return true;

        // op on s1: swap j = 2 and i = 0
        char t = s1[2];
        s1[2] = s1[0];
        s1[0] = t;
        if( s1 == s2 )
            return true;
        // back track
        t = s1[2];
        s1[2] = s1[0];
        s1[0] = t;

        // op on s1: swap j = 3 and i = 1
        t = s1[3];
        s1[3] = s1[1];
        s1[1] = t;
        if( s1 == s2 )
            return true;
        // back track
        t = s1[3];
        s1[3] = s1[1];
        s1[1] = t;

        // op on s1: swap j = 2 and i = 0 and swap j = 3 and i = 1
        t = s1[2];
        s1[2] = s1[0];
        s1[0] = t;
        t = s1[3];
        s1[3] = s1[1];
        s1[1] = t;
        if( s1 == s2 )
            return true;

        return false;
    }
};
