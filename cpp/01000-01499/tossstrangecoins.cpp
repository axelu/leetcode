
// 1230. Toss Strange Coins
// https://leetcode.com/problems/toss-strange-coins/



/* let dp[i][j] be the probability to get j heads when tossing i coins
 *
 * example1 dp[3][1] : probability of one head when tossing first three coins:
 *   probability of one head when tossing first three coins =
 *      no head when tossing first two coins and third coins is head +
 *      one head when tossing first two coins and third coins is not head
 *    dp[3][1] = (dp[2][0] * prob[3]) + (dp[2][1] * (1-prob[3]))
 *
 * example2 dp[4][2] : probability of two heads when tossing first four coins
 * probability of two heads when tossing first four coins =
 *      one head when tossing first three coins and fourth coins is head +
 *      two head when tossing first three coins and third coins is not head
 *    dp[4][2] = (dp[3][1] * prob[4]) + (dp[3][2] * (1-prob[4]))
 *
 * -> dp[i][j] = (dp[i-1][j-1] * prob[i]) + (dp[i-1][j] * (1-prob[i]))
*/
class Solution {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = prob.size();

        int i,j;
        // double dp[n+1][target+1];
        vector<vector<double>> dp(n+1,vector<double>(target+1,0.0));

        // init for 0 heads
        dp[0][0] = 1.0;
        for(i = 1 ; i <= n; ++i)
            dp[i][0] = dp[i-1][0] * (1-prob[i-1]);

        for(i = 1; i <= n; ++i)
            for(j = 1; j <= min(i,target); ++j)
                dp[i][j] = (dp[i-1][j-1] * prob[i-1]) + (dp[i-1][j] * (1-prob[i-1]));

        return dp[n][target];
    }
};
