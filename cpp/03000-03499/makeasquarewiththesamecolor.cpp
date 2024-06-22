
// 3127. Make a Square with the Same Color
// https://leetcode.com/problems/make-a-square-with-the-same-color/




class Solution {
private:
    bool solve(vector<vector<char>>& grid, int i, int j) {
        // 2x2 square with top left {i,j}
        int cntB = 0, cntW = 0;
        if( grid[i][j] == 'B' )
            ++cntB;
        else
            ++cntW;

        if( grid[i][j+1] == 'B' )
            ++cntB;
        else
            ++cntW;

        if( grid[i+1][j] == 'B' )
            ++cntB;
        else
            ++cntW;

        if( grid[i+1][j+1] == 'B' )
            ++cntB;
        else
            ++cntW;

        return cntB < 2 || cntW < 2;
    }


public:
    bool canMakeSquare(vector<vector<char>>& grid) {

        // in our 3x3 grid, there are 4 2x2 squares

        if( solve(grid, 0, 0) )
            return true;
        if( solve(grid, 0, 1) )
            return true;
        if( solve(grid, 1, 0) )
            return true;
        if( solve(grid, 1, 1) )
            return true;

        return false;
    }
};
