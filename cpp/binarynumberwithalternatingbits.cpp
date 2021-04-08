
// 693. Binary Number with Alternating Bits
// https://leetcode.com/problems/binary-number-with-alternating-bits/



class Solution {
public:
    bool hasAlternatingBits(int n) {
        // 1 <= n <= 2147483647
        if( n == 1 ) return true;

        // go from right (LSB) to left (MSB)
        int t = 0, expect = 1;
        if( n & 1 ) {
            t = 1;
            expect = 0;
        }
        for(int i = 1; i < 32; ++i) {
            if( (n >> i) & 1 ) {
                if( expect == 0 ) return false;
                t += pow(2,i);
                if( t == n ) break; // exit when last set bit reached
                expect = 0;
            } else {
                if( expect == 1 ) return false;
                expect = 1;
            }
        }

        return true;
    }
};
