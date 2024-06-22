
// 3094. Guess the Number Using Bitwise Questions II
// https://leetcode.com/problems/guess-the-number-using-bitwise-questions-ii/




/**
 * Definition of commonBits API.
 * int commonBits(int num);
 */

class Solution {
public:
    int findNumber() {
        // n = number to guess
        // 0 <= n <= 2^30 - 1
        // 0 <= n <= 1073741823
        // 10987654321098765432109876543210
        //   111111111111111111111111111111 1073741823 (30 bits set)

        int ans = 0;

        int commonBits0 = commonBits(0);

        for(int i = 0; i < 30; ++i) {
            int mask = 1<<i;

            int commonBitsi = commonBits(mask);
            if( commonBitsi > commonBits0 )
                ans |= mask;
            // reset
            commonBits(mask);
        }

        return ans;
    }
};
