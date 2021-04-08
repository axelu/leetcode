
// 200. Number of Islands
// https://leetcode.com/problems/number-of-islands/



class Solution {
private:
    int M,N;
    void explore(int row, int col, vector<vector<char>>& grid, int seen[]) {
        if( grid[row][col] == '0' ) return; // water
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;    // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen

        // right
        if( col < N-1 ) explore(row,col+1,grid,seen);
        // down
        if( row < M-1 ) explore(row+1,col,grid,seen);
        // left
        if( col > 0 ) explore(row,col-1,grid,seen);
        // up
        if( row > 0 ) explore(row-1,col,grid,seen);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        M = grid.size();
        N = grid[0].size();

        int seen[M*N]; memset(seen,0,sizeof seen);
        int ans = 0;
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < N; ++j)
                if( grid[i][j] == '1' && seen[i*N+j] == 0 ) { // land we have NOT seen before
                    explore(i,j,grid,seen);
                    ++ans;
                }

        return ans;
    }
};
