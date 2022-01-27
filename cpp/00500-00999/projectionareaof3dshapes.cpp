
// 883. Projection Area of 3D Shapes
// https://leetcode.com/problems/projection-area-of-3d-shapes/


class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size(); // n x n grid
        // v = grid[i][j] represents a tower of v cubes placed on top of the cell (i, j)

        int ans = 0,i,j,mx;
        // from the top: count every cell that is not zero
        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j)
                if( grid[i][j] != 0 ) ++ans;

        // from the front: count max per column
        for(j = 0; j < n; ++j) {
            mx = 0;
            for(i = 0; i < n; ++i)
               mx = max(mx,grid[i][j]);
            ans += mx;
        }

        // from the side: count max per row
        for(i = 0; i < n; ++i) {
            mx = 0;
            for(j = 0; j < n; ++j)
               mx = max(mx,grid[i][j]);
            ans += mx;
        }

        return ans;
    }
};
