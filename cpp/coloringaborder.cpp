
// 1034. Coloring A Border
// https://leetcode.com/problems/coloring-a-border/



class Solution {
private:
    int M,N;
    void explore(int row, int col, vector<vector<int>>& grid, int seen[], int compColor) {
        if( grid[row][col] != compColor ) return; // water aka not our component
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;          // land aka our component, we have seen before
        seen[seenIdx] = 1;                        // mark land aka copmonent as seen

        // right
        if( col < N-1 ) explore(row,col+1,grid,seen,compColor);
        // down
        if( row < M-1 ) explore(row+1,col,grid,seen,compColor);
        // left
        if( col > 0 ) explore(row,col-1,grid,seen,compColor);
        // up
        if( row > 0 ) explore(row-1,col,grid,seen,compColor);
    }

    void colorBorder(int row, int col, vector<vector<int>>& grid, int seen[], int island[],
                     int borderColor) {

        int islandIdx = row*N+col;
        if( !island[islandIdx] ) return;
        if( seen[islandIdx] == 1 ) return;        // land aka our component, we have seen before
        seen[islandIdx] = 1;                      // mark land aka copmonent as seen

        // right
        if( col < N-1 ) {
            if( !island[row*N+(col+1)] ) grid[row][col] = borderColor;
            colorBorder(row,col+1,grid,seen,island,borderColor);
        }
        if( col == N-1 ) grid[row][col] = borderColor;
        // down
        if( row < M-1 ) {
            if( !island[(row+1)*N+col] ) grid[row][col] = borderColor;
            colorBorder(row+1,col,grid,seen,island,borderColor);
        }
        if( row == M-1 ) grid[row][col] = borderColor;
        // left
        if( col > 0 ) {
            if( !island[row*N+(col-1)] ) grid[row][col] = borderColor;
            colorBorder(row,col-1,grid,seen,island,borderColor);
        }
        if( col == 0 ) grid[row][col] = borderColor;
        // up
        if( row > 0 ) {
            if( !island[(row-1)*N+col] ) grid[row][col] = borderColor;
            colorBorder(row-1,col,grid,seen,island,borderColor);
        }
        if( row == 0 ) grid[row][col] = borderColor;
    }
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
        M = grid.size();    // number rows
        N = grid[0].size(); // number cols

        int compColor = grid[r0][c0];
        int seen1[M*N]; memset(seen1,0,sizeof seen1);
        int seen2[M*N]; memset(seen2,0,sizeof seen2);
        explore(r0,c0,grid,seen1,compColor);
        colorBorder(r0,c0,grid,seen2,seen1,color);
        return grid;
    }
};
