
// 397. Integer Replacement
// https://leetcode.com/problems/integer-replacement/



class Solution {
private:
    int findRightMostUnsetBit(unsigned int x) {
        int ret = 0;
        while( x & 1U ) {
            x = x >> 1;
            ++ret;
        }
        return ret;
    }

public:
    int integerReplacement(int n) {

        // rightmost bit == 0 -> even else odd
        // operation 1: If n is even, replace n with n / 2.
        // divide by 2 -> right shift
        // operation 2: If n is odd, replace n with either n + 1 or n - 1.
        // subtract 1  -> set right most bit to 0
        // add 1       -> flip all the bits after the rightmost 0 bit and
        //                flip the rightmost 0 bit also.

        int ans = 0;
        unsigned int x = n;
        int t;
        while( x > 1 ) {
            if( !(x & 1U) ) { // even
                x = x >> 1;
                ++ans;
            } else if( x == 3 ) {
                ans += 2;
                break;
            } else {
                t = findRightMostUnsetBit(x);
                if( t == 1 ) {
                    x = x >> 2;
                    ans += 3;
                } else {
                    x = x >> t;
                    x |= 1U;
                    ans += t + 1;
                }
            }
        }

        return ans;
    }
};
