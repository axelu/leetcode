
// 733. Flood Fill
// https://leetcode.com/problems/flood-fill/



class Solution {
private:
    int M,N;
    void explore(int row, int col, vector<vector<int>>& grid, int oldColor, int newColor) {
        if( grid[row][col] != oldColor ) return;
        grid[row][col] = newColor;

        // right
        if( col < N-1 ) explore(row,col+1,grid,oldColor,newColor);
        // down
        if( row < M-1 ) explore(row+1,col,grid,oldColor,newColor);
        // left
        if( col > 0 ) explore(row,col-1,grid,oldColor,newColor);
        // up
        if( row > 0 ) explore(row-1,col,grid,oldColor,newColor);
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int oldColor = image[sr][sc];
        if( oldColor == newColor ) return image;
        M = image.size();
        N = image[0].size();
        explore(sr,sc,image,oldColor,newColor);
        return image;
    }
};
