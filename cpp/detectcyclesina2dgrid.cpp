
// 1559. Detect Cycles in 2D Grid
// https://leetcode.com/problems/detect-cycles-in-2d-grid/





class Solution {
private:
    // four directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    bool explore(vector<vector<char>>& grid, int m, int n, int i, int j,
                 int seen[], int pi, int pj) {

        seen[i*n+j] = 1;

        bool res = false;
        int i_new,j_new;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            j_new = j+dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            // is this a different letter?
            if( grid[i_new][j_new] != grid[i][j] )
                continue;

            // is this where we came from?
            if( i_new == pi && j_new == pj )
                continue;

            // we have seen this cell before?
            if( seen[i_new*n+j_new] )
                return true;

            if( explore(grid,m,n,i_new,j_new,seen,i,j) )
                return true;
        }
        return false;
    }

public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int seen[m*n];memset(seen,0,sizeof seen);

        int seenIdx;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {

                if( !seen[i*n+j] ) { // cell not seen

                    // DFS start at every unseen cell
                    if( explore(grid,m,n,i,j,seen,-1,-1) )
                        return true;

                }
            }
        }
        return false;
    }
};
