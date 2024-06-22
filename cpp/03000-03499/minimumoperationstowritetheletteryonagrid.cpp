
// 3071. Minimum Operations to Write the Letter Y on a Grid
// https://leetcode.com/problems/minimum-operations-to-write-the-letter-y-on-a-grid/




class Solution {
private:
    int n;

    bool is_y_cell(int i, int j) {
        // vertical line starting at the center cell and ending at the bottom border
        if( i >= n/2 )
            return j == n/2;

        // diagonal starting at the top-left cell and ending at the center cell
        if( j < n/2 )
            return i == j;

        // diagonal starting at the top-right cell and ending at the center cell
        j = (n-1) - j;
        return i == j;
    }

public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        n = grid.size(); // n x n grid; n is odd; 3 <= n <= 49; grid[r][c] is 0, 1, or 2

        // if we make the Y all 0s, then we must make all non-Y either 1 OR 2
        // if we make the Y all 1s, then we must make all non-Y either 0 or 2
        // if we make the Y all 2s, then we must make all non-Y either 0 or 1

        // so let us count and then take the best combination
        int y[3]; memset(y,0,sizeof y);
        int non_y[3]; memset(non_y,0,sizeof non_y);

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if( is_y_cell(i,j) )
                    ++y[grid[i][j]];
                else
                    ++non_y[grid[i][j]];

        int ans = INT_MAX;
        ans = min(ans, y[1] + y[2] + min(non_y[0] + non_y[2], non_y[0] + non_y[1]));
        ans = min(ans, y[0] + y[2] + min(non_y[1] + non_y[2], non_y[0] + non_y[1]));
        ans = min(ans, y[0] + y[1] + min(non_y[1] + non_y[2], non_y[0] + non_y[2]));

        return ans;
    }
};
