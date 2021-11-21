
// 1254. Numer of Closed Islands
// https://leetcode.com/problems/number-of-closed-islands/



class Solution {
private:
    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    bool explore(vector<vector<int>>& grid, int m, int n, int i, int j, int seen[]) {
        // return false if our island touches the grid's border
        int seenIdx = i*n+j;
        seen[seenIdx] = 1;

        bool f = true;

        int i_new,j_new;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new == m ) {
                f = false;
                continue;
            }
            j_new = j+dirC[k];
            if( j_new < 0 || j_new == n ) {
                f = false;
                continue;
            }

            // water?
            if( grid[i_new][j_new] )
                continue;
            // land not seen?
            if( seen[i_new*n+j_new] )
                continue;

            bool t = explore(grid,m,n,i_new,j_new,seen);
            if( !t ) f = false;
        }
        return f;
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int seen[m*n];memset(seen,0,sizeof seen);
        int ans = 0;

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( !grid[i][j] && !seen[i*n+j] ) { // land not seen before
                    if( explore(grid,m,n,i,j,seen) )
                        ++ans;
                }
            }
        }

        return ans;
    }
};
