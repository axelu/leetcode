
// 3130. Find All Possible Stable Binary Arrays II
// https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/



// see also 3129. Find All Possible Stable Binary Arrays I
// https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/ 
// same question just smaller constraints.







/* had to look at other solutions such as below in order to solve it
 * https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/discuss/5084709/Simple-2D-DP-%2B-Prefix-Sums-or-90-ms
 * https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/discuss/5080781/Dp%2B-sliding-Window-solution
 *
 * depicting our binary string
 * 0,...,0,1,...,1,...,0,...,0,1,...,1
 * ------- -------     ------- -------
 *    0s      1s   ....    0s     1s
 *
 * we can start with 0's or 1's and we can end with 0's or 1's
 * if we start with 0 and have x groups of consecutive 0s,
 *    we will either have x-1 groupds of consecutive 1s and we end in a groupd of consecutive 0s OR
 *    we will have x groupds of consecutive 1s and we end in a groupd of consecutive 1s.
 * if we start with 1 and have x groups of consecutive 1s,
 *    we will either have x-1 groupds of consecutive 0s and we end in a groupd of consecutive 1s OR
 *    we will have x groupds of consecutive 0s and we end in a groupd of consecutive 0s.
 *  example [0,0,1,0,1,1]: splits into [0,0], [1], [0], [1,1], we have    2 groups of 0s and 2 groups of 1s
 *  example [1,0,1,0,0,1]: splits into [1], [0], [1], [0,0], [1], we have 2 groups of 0s and 3 groups of 0s
 *
 */
class Solution {
private:
    const long mod = 1000000007;
public:
    int numberOfStableArrays(int zero, int one, int limit) {

        // let dp[i][j][0] be the number of sequences with i 0s and j 1s ending in 0, respectively
        // let dp[i][j][1] be the number of sequences with i 0s and j 1s ending in 1
        long dp[zero+1][one+1][2]; memset(dp,0,sizeof dp);

        // base case
        // we have one way to have upto limit 0s or 1s consecutively
        for(int k = 1; k <= min(zero,limit); ++k)
            dp[k][0][0] = 1;
        for(int k = 1; k <= min(one,limit); ++k)
            dp[0][k][1] = 1;

        for(int i = 1; i <= zero; ++i) {
            for(int j = 1; j <= one; ++j) {

                // a sequence ending in 0 can be obtained by appending a single 0
                // to a sequence with one less zero ending in 1, which would be dp[i-1][j][1].
                // further we can append 0s to sequences ending in 0, unless we already have limit number of 0s, so
                // dp[i-1][j][0] - dp[i-limit-1][j][1]
                dp[i][j][0] = (dp[i-1][j][0] + dp[i-1][j][1]) % mod;
                if( i > limit )
                    dp[i][j][0] = (dp[i][j][0] + mod - dp[i-limit-1][j][1]) % mod;

                // see comment above, adapt for sequence ending in 1 instead
                dp[i][j][1] = (dp[i][j-1][0] + dp[i][j-1][1]) % mod;
                if( j > limit )
                    dp[i][j][1] = (dp[i][j][1] + mod - dp[i][j-limit-1][0]) % mod;
            }
        }

        return (dp[zero][one][0] + dp[zero][one][1]) % mod;
    }
};
