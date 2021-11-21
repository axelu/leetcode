
// 1293. Shortest Path in a Grid with Obstacles Elimination
// https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/




class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        if( m == 1 && n == 1 )
            return 0;

        // directions
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};

        // BFS
        queue<array<int,4>> q; // i,j,step,remaining k
        int seen[m][n][k+1];memset(seen,0,sizeof seen);
        // grid[0][0] will be 0
        q.push({0,0,0,k});
        int i,j,step,r,p,i_new,j_new,r_new;
        while(!q.empty()) {
            i    = q.front()[0];
            j    = q.front()[1];
            step = q.front()[2];
            r    = q.front()[3];
            q.pop();

            // explore in all directions
            for(int p = 0; p < 4; ++p) {

                i_new = i+dirR[p];
                if( i_new < 0 || i_new >= m )
                    continue;

                j_new = j+dirC[p];
                if( j_new < 0 || j_new >= n )
                    continue;

                // end?
                // grid[m-1][n-1] will be 0
                if( i_new == m-1 && j_new == n-1 )
                    return step+1;

                // obstacle?
                if( grid[i_new][j_new] == 1 ) {
                    if( r == 0 ) continue;
                    else r_new = r-1;
                } else {
                    r_new = r;
                }

                 if( seen[i_new][j_new][r_new] )
                    continue;

                seen[i_new][j_new][r_new] = 1;
                q.push({i_new,j_new,step+1,r_new});
            }
        }
        return -1;
    }
};
