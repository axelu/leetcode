
// 2304. Minimum Path Cost in a Grid
// https://leetcode.com/problems/minimum-path-cost-in-a-grid/




class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        // bottom up

        // array will contain the min cost to reach bottom row

        int _b[n];  // below row
        for(int i = 0; i < n; ++i)
            _b[i] = grid[m-1][i];

        int _c[n];  // current row

        int * b = _b;
        int * c = _c;

        for(int i = m-2; i >= 0; --i) {     // current row
            for(int j = 0; j < n; ++j) {
                // from each cell in the current row
                // we can go to each cell in the row below
                // cost to reach bottom from current cell =
                //     cost to visit the current cell +
                //     move cost +
                //     cost to reach bottom from the 'moved to cell'

                int x = grid[i][j]; // cost to visit the current cell
                int t = INT_MAX;

                for(int k = 0; k < n; ++k)
                    t = min(t,x + moveCost[x][k] + b[k]);

                c[j] = t;
            }
            // swap
            int * park = c;
            c = b;
            b = park;
        }

        int ans = INT_MAX;
        for(int i = 0; i < n; ++i)
            ans = min(ans,b[i]);

        return ans;
    }
};
