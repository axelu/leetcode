
// 1260. Shift 2D Grid
// https://leetcode.com/problems/shift-2d-grid/


class Solution {
private:
    size_t n,m;

    vector<int> grid2vector(vector<vector<int>>& grid) {
        vector<int> v(n*m);
        int l = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                v[l] = grid[i][j];
                ++l;
            }
        return v;
    }

    vector<vector<int>> vector2grid(vector<int> v, int k) {
        vector<vector<int>> grid(n, vector<int>(m));

        // rotate
        auto s = v.size();
        if( k > s ) k %= s;
        rotate(v.rbegin(), v.rbegin() + k, v.rend());

        int l = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                grid[i][j] = v[l];
                ++l;
            }

        return grid;
    }
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        n = grid.size();
        m = grid[0].size();

        return vector2grid(grid2vector(grid),k);
    }
};
