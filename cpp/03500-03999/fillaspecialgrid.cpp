
// 3537. Fill a Special Grid
// https://leetcode.com/problems/fill-a-special-grid/d




class Solution {
private:
    int rec(vector<vector<int>>& grid, int x0, int y0, int x1, int y1, int idx) {
        // cout << "rec x0 " << x0 << " y0 " << y0 << " x1 " << x1 << " y1 " << y1 << " idx " << idx << endl;
        if( x0 == x1 ) {
            grid[x0][y0] = idx;
            return idx + 1;
        }

        //  ... 0 1 2 3 4 5 6 7
        //  0              x1,y1   top right
        //  1   x0,y0.             bottom left
        //  2
        //  ...

        int n  = y1 - y0 + 1;
        int n2 = n/2;

        // our area covers n x n
        //                  x0           y0            x1          y1
        //              -----------  -----------  -----------  -----------
        idx = rec(grid, x1 + n2 - 1, y1 - n2 + 1,       x1   ,     y1    , idx); // quadrant 0
        idx = rec(grid,     x0     , y1 - n2 + 1,    x1 + n2 ,     y1    , idx); // quadrant 1
        idx = rec(grid,     x0     ,     y0     ,    x1 + n2 ,   y1 - n2 , idx); // quadrant 2
        idx = rec(grid, x1 + n2 - 1,     y0     ,       x1   ,   y1 - n2 , idx); // quadrant 3

        return idx;
    }
public:
    vector<vector<int>> specialGrid(int n) {
        // 0 <= n <= 10
        // 1x1 <= gridsize <= 1024x1024
        // there are only 11 grid sizes
        // n =  0    1 x    1
        // n =  1    2 x    2
        // n =  2    4 x    4
        // n =  3    8 x    8
        // n =  4   16 x   16
        // n =  5   32 x   32
        // n =  6   64 x   64
        // n =  7  128 x  128
        // n =  8  256 x  256
        // n =  9  512 x  512
        // n = 10 1024 x 1024

        if( n == 0 )
            return {{0}};

        // let us work in pattern
        //     3 0
        //     2 1

        int _n = pow(2,n);
        vector<vector<int>> grid(_n, vector<int>(_n));
        rec(grid, _n-1, 0, 0, _n-1, 0);

        return grid;
    }
};
