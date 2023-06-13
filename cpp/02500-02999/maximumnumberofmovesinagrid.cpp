
// 2684. Maximum Number of Moves in a Grid
// https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/




class Solution {
private:
    int m,n;

    int dirR[3] = {-1, 0, 1};
    int dirC[3] = { 1, 1, 1};

    int rec(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& mem) {
        // cout << "rec i " << i << " j " << j << endl;

        if( mem[i][j] != -1 )
            return mem[i][j];

        int ret = 0;

        for(int k = 0; k < 3; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[k];
            if( j_new == n )
                continue;

            if( grid[i_new][j_new] <= grid[i][j] )
                continue;

            int t = rec(grid,i_new,j_new,mem);
            ret = max(ret,t);
        }

        return mem[i][j] = 1 + ret;
    }

public:
    int maxMoves(vector<vector<int>>& grid) {
        m = grid.size();     // rows
        n = grid[0].size();  // cols

        int ans = 0;

        vector<vector<int>> mem(m,vector<int>(n,-1));
        int j = 0;
        for(int i = 0; i < m; ++i) {
            for(int k = 0; k < 3; ++k) {
                int i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;

                int j_new = j + dirC[k];
                if( j_new == n )
                    continue;

                if( grid[i_new][j_new] <= grid[i][j] )
                    continue;

                int t = rec(grid,i_new,j_new,mem);
                ans = max(ans,t);
            }
        }

        return ans;
    }
};
