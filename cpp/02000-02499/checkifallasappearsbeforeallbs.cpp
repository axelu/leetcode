
// 2124. Check if All A's Appears Before All B's
// https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/


class Solution {
public:
    bool checkString(string s) {
        // largest index of a has to be smaller
        // than smallest index of b

        bool hasB = false;
        for(char c : s) {
            if( c == 'a' && hasB )
                return false;
            if( c == 'b' )
                hasB = true;
        }
        return true;
    }
};
