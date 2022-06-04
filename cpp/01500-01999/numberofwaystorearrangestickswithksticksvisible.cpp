
// 1866. Number of Ways to Rearrange Sticks With K Sticks Visible
// https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/


class Solution {
private:
    long mod = 1000000007;
    
    // Returns factorial of n mod 10e9+7
    long fact(long n) {
        long res = 1;
        for(long i = 2; i <= n; ++i)
            res = (res * i) % mod;
        return res;
    }
    
public:
    int rearrangeSticks(int n, int k) {
        // insights:
        //    if the number of sticks n equals the number of visible sticks k
        //        there is only one possible arrangment
        //    if we want one visible stick, then all other sticks must be hidden,
        //        meaning we place the largest stick at position 0, we  have
        //        (number of sticks - 1)! arrangements aka permutations
        if( k == n )
            return 1;
        
        if( k == 1 )
            return fact(n-1);
        
        long dp[n+1][k+1]; // number sticks, number visible sticks
        dp[1][1] = 1;
        for(int i = 2; i <= n; ++i) {
     		// number of arrangements with 1 out of i sticks visible -> (i-1)!
            dp[i][1] = (dp[i-1][1] * (i-1)) % mod;
        }
        
        for(int j = 2; j <= k; ++j) {        // number of visible sticks
            dp[j][j] = 1; // number of arrangements with j out of j sticks visible -> 1
			
            for(int i = j+1; i <= n; ++i) {  // number of sticks
                // add next bigger stick to permutation                 
                // dp[i][j] = number of permutations with j out of i sticks visible
                dp[i][j] = (dp[i-1][j-1] + (dp[i-1][j] * (i-1)) % mod) % mod;
            }
        }
        
        return dp[n][k];    
    }
};

