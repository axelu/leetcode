
// 3418. Maximum Amount of Money Robot Can Earn
// https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/




class Solution {
private:
    int m, n;
    const int INF = 250000001;
    int mem[500][500][3];

    int rec(vector<vector<int>>& grid, int i, int j, int k) {
        if( i == m-1 && j == n-1 ) {
            if( grid[i][j] < 0 && k > 0 )
                return 0;
            return grid[i][j];
        }

        if( mem[i][j][k] != -INF )
            return mem[i][j][k];

        // we have a choice
        //    go right OR
        //    go left
        // if our cell is negative and we still have the ability to
        // neutralize a robber, we have a choice to do so or not

        int ret = -INF;

        if( j + 1 < n ) {
            if( grid[i][j] < 0 ) {
                if( k > 0 )
                    ret = max(ret, rec(grid, i, j+1, k-1));
                ret = max(ret, grid[i][j] + rec(grid, i, j+1, k));
            } else {
                ret = max(ret, grid[i][j] + rec(grid, i, j+1, k));
            }
        }

        if( i + 1 < m ) {
            if( grid[i][j] < 0 ) {
                if( k > 0 )
                    ret = max(ret, rec(grid, i+1, j, k-1));
                ret = max(ret, grid[i][j] + rec(grid, i+1, j, k));
            } else {
                ret = max(ret, grid[i][j] + rec(grid, i+1, j, k));
            }
        }

        return mem[i][j][k] = ret;
    }



public:
    int maximumAmount(vector<vector<int>>& coins) {
        m = coins.size();    // rows
        n = coins[0].size(); // cols

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                for(int k = 0; k <= 2; ++k)
                    mem[i][j][k] = -INF;

        return rec(coins, 0,0,2);
    }
};
