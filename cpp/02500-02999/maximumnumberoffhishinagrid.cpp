
// 2658. Maximum Number of Fish in a Grid
// https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/





class Solution {
private:
    int m,n;

    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    int explore(vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& seen) {

        seen[i][j] = true;
        int ret = grid[i][j];

        // explore all for directions
        for(int k = 0; k < 4; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            if( grid[i_new][j_new] == 0 || seen[i_new][j_new] )
                continue;

            ret += explore(grid,i_new,j_new,seen);
        }

        return ret;
    }

public:
    int findMaxFish(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols


        int ans = 0;

        vector<vector<bool>> seen(m, vector<bool>(n,false));

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 0 || seen[i][j] == true )
                    continue;

                ans = max(ans, explore(grid,i,j,seen));
            }
        }

        return ans;
    }
};
