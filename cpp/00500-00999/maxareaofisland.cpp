
// 695. Max Area of Island
// https://leetcode.com/problems/max-area-of-island/



class Solution {
private:
    int M,N;
    int explore(int row, int col, vector<vector<int>>& grid, int seen[]) {
        if( grid[row][col] == 0 ) return 0; // water
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return 0;  // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen
        int area = 1;

        // right
        if( col < N-1 ) area += explore(row,col+1,grid,seen);
        // down
        if( row < M-1 ) area += explore(row+1,col,grid,seen);
        // left
        if( col > 0 ) area += explore(row,col-1,grid,seen);
        // up
        if( row > 0 ) area += explore(row-1,col,grid,seen);

        return area;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();

        int seen[M*N]; memset(seen,0,sizeof seen);
        int ans = 0;
        int area;
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < N; ++j)
                if( grid[i][j] == 1 && seen[i*N+j] == 0 ) { // land we have NOT seen before
                    area  = explore(i,j,grid,seen);
                    ans = max(ans,area);
                }

        return ans;
    }
};
