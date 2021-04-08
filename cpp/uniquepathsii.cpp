
// Unique Paths II
// https://leetcode.com/problems/unique-paths-ii/


#include <iostream>
#include <cassert>

#include <vector>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        xend = obstacleGrid[0].size();
        yend = obstacleGrid.size();

        if( obstacleGrid[0][0] == 1 ||
            obstacleGrid[yend - 1][xend - 1] == 1)
                return 0;

        // brute force
/*        countPath = 0;
        _bf(0,0,obstacleGrid);
        return countPath; */

        // dynamic programming
        return _dp(obstacleGrid);
    }
private:
    int countPath;
    int xend;
    int yend;

    void _bf(int x, int y, vector<vector<int>>& grid) {

        // outside
        if( x == xend || y == yend ) return;

        // obstacle
        if( grid[y][x] == 1 ) return;

        // visited
        if( grid[y][x] == -2 ) return;

        // end
        if( y == yend - 1 && x == xend - 1 ) {
            ++countPath;
            return;
        }

        grid[y][x] = -2; // mark as visited;

        // east x + 1 aka right
        _bf(x + 1, y, grid);
        // south y + 1 aka down
        _bf(x, y + 1, grid);

        grid[y][x] = 0; // reset to not visited;
    }

    int _dp(vector<vector<int>>& grid) {
        auto m = grid.size();
        auto n = grid[0].size();
        // vector is 0 indexed!!!
        vector<vector<int>> dp(m, vector<int> (n, 1));

        // pre-processing row 0
        // anything right from an obstacle must be set to 0
        bool obstacle = false;
        for(int i = 1; i < n; ++i) {
            if( grid[0][i] == 1 ) {
                obstacle = true;
                continue;
            }
            if ( obstacle ) dp[0][i] = 0;
        }

        // pre-processing column 0
        // anything down from an obstacle must be set to 0
        obstacle = false;
        for(int i = 1; i < m; ++i) {
            if( grid[i][0] == 1 ) {
                obstacle = true;
                continue;
            }
            if ( obstacle ) dp[i][0] = 0;
        }

        // because our robot can only move down or right, the
        // number of paths to the lower rigth corner is the
        // sum of paths it takes to get to the sqare above and
        // to the sqare to the left
        for(int i = 1; i < m; ++i) {
            for(int k = 1; k < n; ++k) {
                // sqare above is obstacle -> don't count
                int sa = ( grid[i-1][k] == 1 ) ? 0 : dp[i-1][k];
                // square to the left is obstacle -> don't count
                int sl = ( grid[i][k-1] == 1 ) ? 0 : dp[i][k-1];

                dp[i][k] = sa + sl;
            }
        }

        return dp[m-1][n-1];
    }
};

int main() {

    Solution s;
    vector<vector<int>> grid;
    int capacity;

    grid = {{0,0,0},{0,1,0},{0,0,0}}; // 2
    cout <<  s.uniquePathsWithObstacles(grid) << endl;
    // assert(s.uniquePathsWithObstacles(grid) == 2);

    grid = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}; // 28
    cout <<  s.uniquePathsWithObstacles(grid) << endl;
    // assert(s.uniquePathsWithObstacles(grid) == 28);

    grid = {{0,1,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}; // 0
    cout <<  s.uniquePathsWithObstacles(grid) << endl;
    // assert(s.uniquePathsWithObstacles(grid) == 0);

    grid = {{1}}; // 0
    cout <<  s.uniquePathsWithObstacles(grid) << endl;
    // assert(s.uniquePathsWithObstacles(grid) == 0);

    grid = {{1,0,0},{0,0,0},{0,0,0}}; // 0
    cout <<  s.uniquePathsWithObstacles(grid) << endl;
    // assert(s.uniquePathsWithObstacles(grid) == 0);

    grid = {{0,0,0},{0,0,0},{0,0,1}}; // 0
    cout <<  s.uniquePathsWithObstacles(grid) << endl;
    // assert(s.uniquePathsWithObstacles(grid) == 0);

    return 0;
}
