
// 1411. Number of Ways to Paint N × 3 Grid
// https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/




/*
 * each 3 color permutation can be combined with 4 options
 * each 2 color permutation cab be combined with 5 options
 *           - row 0 3 color perms - - row 0 2 color perms -
 * row 0     GRY GYR RYG RGY YRG YGR RYR YRY GYG YGY GRG RGR
 * row 1     RYG RGY YGR GYG RGY GRY YGY ...
 *           RYR YRG YRY GYG RGY GRY YRY ...
 *           YGR YRY GRY YRG GYR RYG GRG ...
 *           RGR YGY YGY GRG RYR GYG GRY ...
 *                                   YRG ...
 * so for 2 rows then, we get:
 *     6 * 4 + 6 * 5 = 54 options
 *
 * 3 color perms can be combined with 4 options, out of we will have
 *     2 x 2 color and 2 x 3 color
 * 2 color perms can be combined with 5 options, out of we will have
 *     3 x 2 color and 2 x 3 color
 *
*/
class Solution {
public:
    int numOfWays(int n) {
        // n = 1 -> ans =   12
        // n = 2 -> ans =   54
        // n = 3 -> ans =  246
        // n = 4 -> ans = 1122

        long mod = 1000000007;

        long three_colors_pre = 6;
        long two_colors_pre   = 6;

        for(int i = 2; i <= n; ++i) {

            // the number of previous three colors multiplies into
            //    2x three colors and 2x two colors
            long three_colors_cur = (2 * three_colors_pre) % mod;
            long two_colors_cur   = (2 * three_colors_pre) % mod;

            // the number of previous two colors multiplies into
            //    2x three colors and 3x two colors
            three_colors_cur = (three_colors_cur + ((2 * two_colors_pre) % mod)) % mod;
            two_colors_cur   = (two_colors_cur   + ((3 * two_colors_pre) % mod)) % mod;

            three_colors_pre = three_colors_cur;
            two_colors_pre   = two_colors_cur;
            // debug
            // cout << i << " rows -> 3 colors: " << three_colors_pre << " 2 colors: " << two_colors_pre << endl;
        }

        return (two_colors_pre + three_colors_pre) % mod;
    }
};
