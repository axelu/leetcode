
// 463. Island Perimeter
// https://leetcode.com/problems/island-perimeter/



class Solution {
private:
    int M,N;
    int ans;
    void explore(int row, int col, vector<vector<int>>& grid, int seen[]) {
        if( grid[row][col] == 0 ) { // water
            ++ans;
            return;
        }
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;    // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen

        // right
        if( col < N-1  ) explore(row,col+1,grid,seen);
        if( col == N-1 ) ++ans;
        // down
        if( row < M-1  ) explore(row+1,col,grid,seen);
        if( row == M-1 ) ++ans;
        // left
        if( col > 0  ) explore(row,col-1,grid,seen);
        if( col == 0 ) ++ans;
        // up
        if( row > 0  ) explore(row-1,col,grid,seen);
        if( row == 0 ) ++ans;
    }

public:
    int islandPerimeter(vector<vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();

        int seen[M*N]; memset(seen,0,sizeof seen);
        ans = 0;
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < N; ++j) {
                if( grid[i][j] == 1 ) { // land
                    explore(i,j,grid,seen);
                    break;
                }
            }
            if( ans != 0 ) break;
        }
        return ans;
    }
};
