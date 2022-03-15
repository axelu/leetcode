
// 1692. Count Ways to Distribute Candies
// https://leetcode.com/problems/count-ways-to-distribute-candies/



class Solution {
private:
    long mod = 1000000007;

    long mem[1001][1001]; // candies,bags

    long rec(int i, int k) {

        if( mem[i][k] != -1L )
            return mem[i][k];

        // from the hints
        // there will be one of two ways to distribute the ith candy:
        //     if the i-1 previous candies are already distributed into k bags,
        //      we can have k * dp[n - 1][k] ways to distribute the ith candy.
        //     if the i-1 previous candies are already distributed into k - 1 bags,
        //      we can have dp[n - 1][k - 1] ways to distribute the ith candy.

        long ret = (((k * rec(i-1,k)) % mod) + rec(i-1,k-1)) % mod;

        return mem[i][k] = ret;
    }

public:
    int waysToDistribute(int n, int k) {
        // 1 <= k <= n <= 1000
        if( k == 1 || n == k )
            return 1;

        // if number candies == number bags OR
        // if only one bag left
        // then only one way to distribute the candy
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= k; ++j)
                mem[i][j] = ( j == 1 || i == j ) ? 1L : -1L;

        return rec(n,k);
    }
};
