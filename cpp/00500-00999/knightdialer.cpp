
// 935. Knight Dialer
// https://leetcode.com/problems/knight-dialer/


class Solution {
public:
    int knightDialer(int n) {
        if( n == 1 )
            return 10;

        // let dp[i][j] the number of distinct phone numbers from key j
        //              if there are i jumps left

        long dp[n+1][10];
        dp[1][0] = 2;
        dp[1][1] = 2;
        dp[1][2] = 2;
        dp[1][3] = 2;
        dp[1][4] = 3;
        dp[1][5] = 0;
        dp[1][6] = 3;
        dp[1][7] = 2;
        dp[1][8] = 2;
        dp[1][9] = 2;

        long mod = 1000000007;
        //                     0     1     2     3      4     5   6       7     8     9
        vector<int> p[10] = {{4,6},{6,8},{7,9},{4,8},{0,3,9},{},{0,1,7},{2,6},{1,3},{2,4}};

        // bottom up
        for(int i = 2; i < n; ++i) {

            for(int j = 0; j < 10; ++j) {
                long t = 0;
                for(int k = 0; k < p[j].size(); ++k)
                    t = (t + dp[i-1][p[j][k]]) % mod;
                dp[i][j] = t;
            }
        }

        long ans = 0;
        for(int j = 0; j < 10; ++j)
            ans = (ans + dp[n-1][j]) % mod;

        return ans;
    }
};
