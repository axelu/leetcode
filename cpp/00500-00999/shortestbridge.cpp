
// 934. Shortest Bridge
// https://leetcode.com/problems/shortest-bridge/




class Solution {
private:
    int M,N;
    int ans;

    void explore1(int row, int col, vector<vector<int>>& grid, int seen[], vector<vector<int>>& island1) {
        if( grid[row][col] == 0 ) return;   // water
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;    // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen
        island1.push_back({row,col});        // add land to our island

        // right
        if( col < N-1 ) explore1(row,col+1,grid,seen,island1);
        // down
        if( row < M-1 ) explore1(row+1,col,grid,seen,island1);
        // left
        if( col > 0 ) explore1(row,col-1,grid,seen,island1);
        // up
        if( row > 0 ) explore1(row-1,col,grid,seen,island1);
    }

    void explore2(int row, int col, vector<vector<int>>& grid, int seen[], vector<vector<int>>& island1) {
        if( grid[row][col] == 0 ) return;   // water
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;    // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen
        // brute force
        for(int i = 0; i < island1.size(); ++i) {
            int y_diff = abs(row-island1[i][0]);
            int x_diff = abs(col-island1[i][1]);
            if( y_diff == 0 ) {
                ans = min(ans,x_diff-1);
            } else if( x_diff == 0 ) {
                ans = min(ans,y_diff-1);
            } else {
                ans = min(ans,x_diff+y_diff-1);
            }
        }

        // right
        if( col < N-1 ) explore2(row,col+1,grid,seen,island1);
        // down
        if( row < M-1 ) explore2(row+1,col,grid,seen,island1);
        // left
        if( col > 0 ) explore2(row,col-1,grid,seen,island1);
        // up
        if( row > 0 ) explore2(row-1,col,grid,seen,island1);
    }


public:
    int shortestBridge(vector<vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();

        int seen[M*N]; memset(seen,0,sizeof seen);
        vector<vector<int>> island1;
        int islandNr = 1;
        ans = INT_MAX;
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < N; ++j) {
                if( grid[i][j] == 1 && seen[i*N+j] == 0 ) { // land we have NOT seen before
                    if( islandNr == 1 ) {
                        explore1(i,j,grid,seen,island1);
                        ++islandNr;
                    } else {
                        explore2(i,j,grid,seen,island1);
                        ++islandNr;
                        break;
                    }
                }
            }
            if( islandNr == 3 ) break;
        }

        return ans;
    }
};
