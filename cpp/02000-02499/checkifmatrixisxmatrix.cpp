

// 2319. Check if Matrix Is X-Matrix
// https://leetcode.com/problems/check-if-matrix-is-x-matrix/

class Solution {
public:
    bool checkXMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        // n == grid.length == grid[i].length
        // 3 <= n <= 100

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if( i == j ||
                    ( i == n-1-j ) ||
                    ( n-1-i == j ) ) {
                    // on diagonal
                    if( grid[i][j] == 0 ) {
                        return false;
                    }
                } else {
                    // not on diagonal
                    if( grid[i][j] != 0 ) {
                        return false;
                    }
                }

        return true;
    }
};
