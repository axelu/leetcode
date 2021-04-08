
// 717. 1-bit and 2-bit Characters
// https://leetcode.com/problems/1-bit-and-2-bit-characters/


class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size();
        if( n == 1 ) return true;

        for(int i = 0; i < n; ++i) {
            if( i == n-1 ) return true;
            if( i == n-2 )
                return bits[i] == 1 ? false : true;

            if( bits[i] == 1 ) ++i;
        }
        // satisfy compiler
        return false;
    }
};
