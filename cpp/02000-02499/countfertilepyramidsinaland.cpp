
// 2088. Count Fertile Pyramids in a Land
// https://leetcode.com/problems/count-fertile-pyramids-in-a-land/



class Solution {
private:
    int m,n;

    int h(vector<vector<int>>& grid, int k, int dp[]) {
        if( dp[k] != -1 )
            return dp[k];

        int i = k / n;
        int j = k % n;
        // we only get here if grid[i][j] == 1

        if( i == m-1 )          // we are in the last row
            return dp[k] = 1;

        if( grid[i+1][j] == 0 ) // the cell below us is 0
            return dp[k] = 1;

        int k_new;

        int hl = 0; // cell [i+1][j-1]
        if( j > 0 && grid[i+1][j-1] == 1 ) {
            k_new = (i+1)*n + (j-1);
            hl = h(grid,k_new,dp);
        }

        int hr = 0; // cell [i+1][j+1]
        if( j < n-1 && grid[i+1][j+1] == 1 ) {
            k_new = (i+1)*n + (j+1);
            hr = h(grid,k_new,dp);
        }

        return dp[k] = 1 + min(hl,hr);
    }

public:
    int countPyramids(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols

        int ans = 0;

        // let dp[k] be the height of the pyramidal plot
        // at i = k / n and j = k % n
        int dp[m*n];memset(dp,-1,sizeof dp);

        // count pyramidal plots
        for(int k = 0; k < m*n; ++k)
            if( grid[k/n][k%n] == 1 )
                ans += dp[k] == -1 ? h(grid,k,dp) - 1 : dp[k] - 1;

        // count inverse pyramidal plots
        // rotate grid by 180deg
        int t = 0, b = m-1;
        while( t < b ) {
            // park the current row
            vector<int> p(grid[t]);
            grid[t] = grid[b];reverse(grid[t].begin(),grid[t].end());
            grid[b] = p;      reverse(grid[b].begin(),grid[b].end());
            ++t;--b;
        }
        if( m % 2 )
            reverse(grid[m/2].begin(),grid[m/2].end());

        memset(dp,-1,sizeof dp);
        for(int k = 0; k < m*n; ++k)
            if( grid[k/n][k%n] == 1 )
                ans += dp[k] == -1 ? h(grid,k,dp) - 1 : dp[k] - 1;

        return ans;
    }
};
