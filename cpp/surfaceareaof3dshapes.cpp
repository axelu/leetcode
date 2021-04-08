
// 892. Surface Area of 3D Shapes
// https://leetcode.com/problems/surface-area-of-3d-shapes/


class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size(); // n x n grid

        int ans = 0, a;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] > 0 ) {
                    a = 2; // top and bottom surface
                    // north surface area
                    if( i == 0 ) {
                        a += grid[i][j];
                    } else {
                        if( grid[i-1][j] < grid[i][j] )
                            a += grid[i][j] - grid[i-1][j];
                    }
                    // east surface area
                    if( j == n-1 ) {
                        a += grid[i][j];
                    } else {
                        if( grid[i][j+1] < grid[i][j] )
                            a += grid[i][j] - grid[i][j+1];
                    }
                    // south surface area
                    if( i == n-1 ) {
                        a += grid[i][j];
                    } else {
                        if( grid[i+1][j] < grid[i][j] )
                            a += grid[i][j] - grid[i+1][j];
                    }
                    // west surface area
                   if( j == 0 ) {
                        a += grid[i][j];
                    } else {
                        if( grid[i][j-1] < grid[i][j] )
                            a += grid[i][j] - grid[i][j-1];
                    }
                    ans += a;
                }
            }
        }
        return ans;
    }
};
