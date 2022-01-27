
// 1318. Minimum Flips to Make a OR b Equal to c
// https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/


/*
 * cases/logic up to and including left most set bit in c
 * a    1  0  1  0
 * b    1  1  0  0
 * c 1          +1
 * c 0 +2 +1 +1
*/

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int c_lm = 0; // left most bit that is set in c
        for(int i = 0; i < 30; ++i)
            if( (c >> i) & 1 )
                c_lm = i;

        int ans = 0;
        int i = 0;
        int a_bit,b_bit;

        // up to and including left most set bit in c
        for(; i <= c_lm; ++i) {
            a_bit = (a >> i) & 1;
            b_bit = (b >> i) & 1;
            if( (c >> i) & 1 ) {
                if( !a_bit && !b_bit )
                    ++ans;

            } else {
                if( a_bit && b_bit )
                    ans += 2;
                else if( a_bit != b_bit)
                    ++ans;
            }
        }

        // remaining bits
        for(; i < 30; ++i) {
            a_bit = (a >> i) & 1;
            b_bit = (b >> i) & 1;
            if( a_bit && b_bit )
                ans += 2;
            else if( a_bit != b_bit)
                ++ans;
        }

        return ans;
    }
};
