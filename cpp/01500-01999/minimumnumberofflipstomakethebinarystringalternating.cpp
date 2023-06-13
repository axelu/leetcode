
// 1888. Minimum Number of Flips to Make the Binary String Alternating
// https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/






// see also 1864. Minimum Number of Swaps to Make the Binary String Alternating
// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/

/* cost vertical 1
 * cost diagonal 2
 *
 * if n is even
 *     we need to have an equal amount of 0s and 1s
 *        if we don't, we need to even that out
 *        greedely flip to support even distribution of of 0s and 1s on odd and even indicies
 *     we need to have 0s and 1s equally distributed on even and odd indicies
 *        when we rotate, we don't make a difference,
 *        because what is on 0 removes to n-1 (which n-1 is an odd index)
 *        so everything moves from odd to even respectively even and odd the same
 *     final state
 *         even odd total        even odd total
 *     0s  n/2   0   n/2    OR    0   n/2  n/2
 *     1s   0   n/2  n/2         n/2   0   n/2
 *
 *
 * if n is odd
 *     what we have more off initially should remain more
 *         and end up being on even indicies (because we have one more even index compared to odd)
 *     the total difference between 0s and 1s must be one
 *     what we have 1 more off needs to be evenly distributed between even and odd indicies
 *     what we have 1 less off needs to be on more on odd
 *
 *     if rotating, 0 moves to n-1, where n-1 is an even index
 *              0 1 2 3 4 5 6       even odd total
 *     example  1 1 0 0 0 0 1    0s   2   2    4
 *                               1s   2   1    3
 *     rotated  1 0 0 0 0 1 1    0s   2   2    4
 *                               1s   2   1    3
 *     rotated  0 0 0 0 1 1 1    0s   2   2    4
 *                               1s   2   1    3
 *     rotated  0 0 0 1 1 1 0    0s   3   1    4  changed !!!
 *                               1s   1   2    3  changed !!!
 *     what is left is 2 flips
 *     final state
 *         even   odd   total        even   odd   total
 *     0s  n/2+1   0     n/2+1   OR    0    n/2    n/2
 *     1s   0     n/2    n/2         n/2+1   0     n/2+1

 */
class Solution {
private:
    int n;
    // 0 0even, 1 0odd, 2 1even, 3 1odd
    // count of above to the left and including i
    int cnts[100001][4];

    void cnt(string& s) {
        int cnt0even = 0, cnt0odd = 0;
        int cnt1even = 0, cnt1odd = 0;
        cnts[0][0] = 0;
        cnts[0][1] = 0;
        cnts[0][2] = 0;
        cnts[0][3] = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                if( i % 2 == 0 )
                    ++cnt0even;
                else
                    ++cnt0odd;
            } else {
                if( i % 2 == 0 )
                    ++cnt1even;
                else
                    ++cnt1odd;
            }
            cnts[i+1][0] = cnt0even;
            cnts[i+1][1] = cnt0odd;
            cnts[i+1][2] = cnt1even;
            cnts[i+1][3] = cnt1odd;
        }
    }

    int solve_even() {
        // n is even
        // in the end, we need
        //   an equal number of 1s and 0s AND
        //     all 0s on even and all 1s on odd OR
        //     all 0s on odd  and all 1s on even

        int nh = n/2;
        int a = nh - cnts[n][0] + nh - cnts[n][3];
        int b = nh - cnts[n][2] + nh - cnts[n][1];

        return min(a,b);
    }

public:
    int minFlips(string s) {
        n = s.size();
        if( n == 1 )
            return 0;

        cnt(s);

        // debug
        // cout << "n " << n << endl;
        // cout << "0s even " << cnts[n][0] << " odd " << cnts[n][1] << endl;
        // cout << "1s even " << cnts[n][2] << " odd " << cnts[n][3] << endl;

        if( n % 2 == 0 )
           return solve_even();

        int cnt0    = cnts[n][0] + cnts[n][1];
        int cnt1    = cnts[n][2] + cnts[n][3];
        int cnteven = cnts[n][0] + cnts[n][2];
        int cntodd  = cnts[n][1] + cnts[n][3];

        // finding the best possible split aka rotation
        int ret = INT_MAX;
        int nh = n/2;
        int cnt1even, cnt1odd, cnt0even, cnt0odd;

        for(int i = 0; i < n; ++i) {
            cnt1even = cnts[i][2] + cnts[n][3] - cnts[i][3];
            cnt1odd  = cnt1 - cnt1even;
            cnt0even = cnts[i][0] + cnts[n][1] - cnts[i][1];
            cnt0odd  = cnt0 - cnt0even;

            int a = nh + 1 - cnt0even + nh - cnt1odd;
            int b = nh + 1 - cnt1even + nh - cnt0odd;

            ret = min({ret,a,b});
        }

        return ret;
    }
};
