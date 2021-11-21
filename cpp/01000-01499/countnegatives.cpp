
// 1351. Count Negative Numbers in a Sorted Matrix
// https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/



class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        auto m = grid.size();
        auto n = grid[0].size();

        // brute force
        int r = 0;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if(grid[i][j] < 0) ++r;

        return r;
    }
};
