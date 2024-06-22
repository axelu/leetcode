
// 3133. Minimum Array End
// https://leetcode.com/problems/minimum-array-end/




/* example n = 4, x = 5 -> ans = 15
 * binary
 *      5   0101
 *      7   0111
 *     12   1101
 *     15   1111
 * observation
 * our sequence will start with x and includes all number > x that have the same bits as x set
 * so taking the example aboge, if we would ask to deliver a sequence of length n = 5
 * example n = 5, x = 5 -> ans = 15 -> ans = 21
 * binary
 *      5  00101  0th
 *      7  00111  1th
 *     12  01101  2nd
 *     15  01111  3rd
 *     21  10101  4th aka n-1'th
 * as observed, we can only use integers that have the same bits as x set
 * so if we distribute the bits of n-1 right to left into ans but skip the bits in x that are set, we have our answer
 * example         6543210
 * x    5   00101    00101
 * n-1  4   00100  0010 0
 * ans             0010101
 */
class Solution {
public:
    long long minEnd(int n, int x) {
        // 1 <= n, x <= 1e8
        // 100000000 -> 101111101011110000100000000 (27 digits)

        long long ans  = (long long)x;
        long long ll_n = (long long)n - 1LL;

        int idx_n   = 0;
        for(int i = 0; i < 54; ++i) { // index in ans
            if( (ans >> i) & 1LL ) {
                // do nothing

            } else {
                // we are at idx_n in n respectively in n-1
                if( (ll_n >> idx_n) & 1LL ) {
                    // we need to set the ith bit in ans
                    long long mask = (1LL << i);
                    ans |= mask;
                }
                ++idx_n;
            }
        }

        return ans;
    }
};
