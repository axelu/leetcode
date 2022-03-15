
// 1359. Count All Valid Pickup and Delivery Options
// https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/

/*
 * n = 1, only 1 possibility (P1,D1)
 * n = 2
 * pattern observation
 * stick the new pair (P2,D2) in the front
 * then we can move D2 all the way to the back
 * P2 D2 P1       D1
 * P2    P1 D2    D1
 * P2    P1       D1     D2
 * that give us 3 options
 * then we can stick the new pair on the position after P1
 *       P1 P2 D2 D1
 *       P1 P2    D1     D2
 * that gives us 2 options
 * and last but not least, we can stick the new pair at the end
 *       P1       D1 P2 D2
 * which give us 1 more possibility
 * -> total 3 + 2 + 1 = 6
 * this can be translated into a formula
 * dp[i] = dp[i-1] * summation
 *                   k = i
 *                   while(k-1>=1)
 *                      t += ((k-1)*2)+1 + ((k-1)*2)
 *                   t += 1;
 */
class Solution {
public:
    int countOrders(int n) {
        if( n == 1 )
            return 1;

        long mod = 1000000007;

        long dp[n+1];
        dp[1] = 1;
        for(int i = 2; i <= n; ++i) {
            long t = 0L;
            for(int k = i; k-1 >= 1; --k)
                t = (t + (((k - 1) * 2 + 1) + ((k - 1) * 2)));
            t += 1L;
            dp[i] = (dp[i-1] * t) % mod;
        }

        return dp[n];
    }
};
