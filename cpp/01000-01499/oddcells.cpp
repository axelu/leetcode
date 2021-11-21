
// 1252. Cells with Odd Values in a Matrix
// https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/


class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        // init matrix
        vector<vector<int>> matrix(n, vector<int>(m,0));

        // process indices
        auto k = indices.size();
        int ri,ci;
        for(int i = 0; i < k; ++i) {
            // process row
            ri = indices[i][0];
            for(int j = 0; j < m; ++j)
                ++matrix[ri][j];
            // process column
            ci = indices[i][1];
            for(int j = 0; j < n; ++j)
                ++matrix[j][ci];
        }

        // count odd cells
        int r = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if( matrix[i][j] % 2 != 0 ) ++r;

        return r;
    }
};
