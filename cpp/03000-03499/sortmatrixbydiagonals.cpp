
// 3446. Sort Matrix by Diagonals
// https://leetcode.com/problems/sort-matrix-by-diagonals/



class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size(); // n x n square matrix; 1 <= n <= 10
        if( n == 1 )
            return grid;

        // fill the bottom-left triangle
        for(int i = 0; i < n-1; ++i) {
            int v_sz = n-i;
            vector<int> v(v_sz);
            // pass1
            int v_idx = 0;
            int r = i;
            for(int j = 0; r < n; ++j, ++r, ++v_idx)
                v[v_idx] = grid[r][j];
            // pass2
            sort(begin(v),end(v),greater<int>());
            v_idx = 0;
            r = i;
            for(int j = 0; r < n; ++j, ++r, ++v_idx)
                grid[r][j] = v[v_idx];
        }

        // fill the top-right triangle
        for(int j = 1; j < n-1; ++j) {
            int v_sz = n-j;
            vector<int> v(v_sz);
            // pass1
            int v_idx = 0;
            int c = j;
            for(int i = 0; c < n; ++i, ++c, ++v_idx)
                v[v_idx] = grid[i][c];
            // pass2
            sort(begin(v),end(v));
            v_idx = 0;
            c = j;
            for(int i = 0; c < n; ++i, ++c, ++v_idx)
                grid[i][c] = v[v_idx];
        }

        return grid;
    }
};
