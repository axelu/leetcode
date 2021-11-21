
// 1219. Path with Maximum Gold
// https://leetcode.com/problems/path-with-maximum-gold/




class Solution {
private:
    int m,n;

    // directions right,down,left,up
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    int explore(vector<vector<int>>& grid, int i, int j, int seen[]) {
        int seenIdx = i*n+j;
        seen[seenIdx] = 1;

        // explore all four directions
        int ans = 0;
        int i_new, j_new;
        for(int k = 0; k < 4; ++k) {
            i_new = i+dirR[k];
            if( i_new < 0 || i_new == m ) continue;
            j_new = j+dirC[k];
            if( j_new < 0 || j_new == n ) continue;

            // is the new cell an empty cell?
            if( grid[i][j] == 0 ) continue;

            // is the new cell already part of our path?
            if( seen[i_new*n+j_new] ) continue;

            ans = max(ans,explore(grid,i_new,j_new,seen));
        }

        // backtracking
        seen[seenIdx] = 0;

        return grid[i][j] + ans;
    }
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size();     // rows
        n = grid[0].size();  // cols

        int seen[m*n];memset(seen,0,sizeof seen);

        int ans = 0;
        // every cell is a potential starting point
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 0 ) continue;
                ans = max(ans,explore(grid,i,j,seen));
            }
        }

        return ans;
    }
};
