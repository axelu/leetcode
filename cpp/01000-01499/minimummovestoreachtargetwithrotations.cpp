
// 1210. Minimum Moves to Reach Target with Rotations
// https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/





class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        // n == grid.size() == grid[i].size(); basically n x n grid
        int n = grid.size();

        // BFS
        queue<array<int,3>> q; // gridIdx of head of snake, 0 horizontal/1 vertical, steps
        int seen[n*n][2];memset(seen,0,sizeof seen);

        q.push({1,0,0});
        seen[1][0] = 1;
        int gridIdx,col,row,orientation,steps,gridIdx_new,col_new,row_new;
        while( !q.empty() ) {
            gridIdx = q.front()[0];
            row = gridIdx/n;
            col = gridIdx%n;
            orientation = q.front()[1];
            steps = q.front()[2];
            q.pop();

            // have we reached the end
            if( row == n-1 && col == n-1 && orientation == 0 )
                return steps;

            // right
            col_new = col+1;
            if( col_new < n ) {
                gridIdx_new = row*n+col_new;
                if( orientation == 0 && grid[row][col_new] == 0 &&
                    !seen[gridIdx_new][0] ) {

                    q.push({gridIdx_new,0,steps+1});
                    seen[gridIdx_new][0] = 1;
                } else if( orientation == 1 && grid[row][col_new] == 0 &&
                          grid[row-1][col_new] == 0 && !seen[gridIdx_new][1] ) {

                    q.push({gridIdx_new,1,steps+1});
                    seen[gridIdx_new][1] = 1;
                }
            }

            // down
            row_new = row+1;
            if( row_new < n ) {
                gridIdx_new = row_new*n+col;
                if( orientation == 0 && grid[row_new][col] == 0 &&
                    grid[row_new][col-1] == 0 && !seen[gridIdx_new][0] ) {

                    q.push({gridIdx_new,0,steps+1});
                    seen[gridIdx_new][0] = 1;
                } else if( orientation == 1 && grid[row_new][col] == 0 &&
                    !seen[gridIdx_new][1] ) {

                    q.push({gridIdx_new,1,steps+1});
                    seen[gridIdx_new][1] = 1;
                }
            }

            // rotate clockwise
            row_new = row+1;
            col_new = col-1;
            if( row_new < n && orientation == 0 ) {
                gridIdx_new = row_new*n+col_new;
                if( grid[row_new][col] == 0 && grid[row_new][col_new] == 0 &&
                    !seen[gridIdx_new][1] ) {

                    q.push({gridIdx_new,1,steps+1});
                    seen[gridIdx_new][1] = 1;
                }
            }

            // rotate counterclockwise
            row_new = row-1;
            col_new = col+1;
            if( col_new < n && orientation == 1 ) {
                gridIdx_new = row_new*n+col_new;
                if( grid[row][col_new] == 0 && grid[row_new][col_new] == 0 &&
                    !seen[gridIdx_new][0] ) {

                    q.push({gridIdx_new,0,steps+1});
                    seen[gridIdx_new][1] = 1;
                }
            }
        }
        return -1;
    }
};
