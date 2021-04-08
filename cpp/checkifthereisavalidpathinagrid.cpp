
// 1391. Check if There is a Valid Path in a Grid
// https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/




class Solution {
private:
    int M,N;
    bool dfs(int row, int col, vector<vector<int>>& grid, int seen[]) {
        if( row == M-1 && col == N-1 ) return true;
        int seenIdx = row*N+col;
        if( seen[seenIdx] ) return false;
        seen[seenIdx] = 1;

        // each tile has 2 possible exits, of which one is the one that we came from
        if( grid[row][col] == 1 ) {
            // left
            if( col > 0 && ( grid[row][col-1] == 1 || grid[row][col-1] == 4 || grid[row][col-1] == 6 ) )
                if( dfs(row,col-1,grid,seen) ) return true;
            // right
            if( col < N-1 && ( grid[row][col+1] == 1 || grid[row][col+1] == 3 || grid[row][col+1] == 5 ) )
                return dfs(row,col+1,grid,seen);
        } else if( grid[row][col] == 2 ) {
            // up
            if( row > 0 && ( grid[row-1][col] == 2 || grid[row-1][col] == 3 || grid[row-1][col] == 4 ) )
                if( dfs(row-1,col,grid,seen) ) return true;
            // down
            if( row < M-1 && ( grid[row+1][col] == 2 || grid[row+1][col] == 5 || grid[row+1][col] == 6 ) )
                return dfs(row+1,col,grid,seen);
        } else if( grid[row][col] == 3 ) {
            // left
            if( col > 0 && ( grid[row][col-1] == 1 || grid[row][col-1] == 4 || grid[row][col-1] == 6 ) )
                if( dfs(row,col-1,grid,seen) ) return true;
            // down
            if( row < M-1 && ( grid[row+1][col] == 2 || grid[row+1][col] == 5 || grid[row+1][col] == 6 ) )
                return dfs(row+1,col,grid,seen);
        } else if( grid[row][col] == 4 ) {
            // right
            if( col < N-1 && ( grid[row][col+1] == 1 || grid[row][col+1] == 3 || grid[row][col+1] == 5 ) )
                if( dfs(row,col+1,grid,seen) ) return true;
            // down
            if( row < M-1 && ( grid[row+1][col] == 2 || grid[row+1][col] == 5 || grid[row+1][col] == 6 ) )
                return dfs(row+1,col,grid,seen);
        } else if( grid[row][col] == 5 ) {
            // left
            if( col > 0 && ( grid[row][col-1] == 1 || grid[row][col-1] == 4 || grid[row][col-1] == 6 ) )
                if( dfs(row,col-1,grid,seen) ) return true;
            // up
            if( row > 0 && ( grid[row-1][col] == 2 || grid[row-1][col] == 3 || grid[row-1][col] == 4 ) )
                return dfs(row-1,col,grid,seen);
        } else if( grid[row][col] == 6 ) {
            // right
            if( col < N-1 && ( grid[row][col+1] == 1 || grid[row][col+1] == 3 || grid[row][col+1] == 5 ) )
                if( dfs(row,col+1,grid,seen) ) return true;
            // up
            if( row > 0 && ( grid[row-1][col] == 2 || grid[row-1][col] == 3 || grid[row-1][col] == 4 ) )
                return dfs(row-1,col,grid,seen);
        }

        return false;
    }
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();

        int seen[M*N]; memset(seen,0,sizeof seen);
        return dfs(0,0,grid,seen);
    }
};
