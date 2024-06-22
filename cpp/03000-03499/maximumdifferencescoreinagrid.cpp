
// 3148. Maximum Difference Score in a Grid
// https://leetcode.com/problems/maximum-difference-score-in-a-grid/

/* example 1
 *     0  1  2  3
 *   0 9  5  7  3
 *   1 8  9  6  1
 *   2 6  7 14  3
 *   3 2  5  3  1
 * the answer is [0,1] -> [2,1] -> [2,2] => (7 - 5) + (14 - 7)
 * observation: the '7' offsets itself, meaning for a given path, only the begin and end matters.
 * so we are looking for a path with smallest begin and largest ending
 * we can go through the grid and treat the current cell as the end of a path and its max while
 * at the same time keep track of the minimum encountered along the way
 */
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // 4 <= m * n <= 1e5

        vector<vector<int>> mem(m,vector<int>(n,INT_MIN));
        // init row 0 and col 0
        for(int j = 0; j < n; ++j)
            mem[0][j] = grid[0][j];
        for(int i = 0; i < m; ++i)
            mem[i][0] = grid[i][0];
        
        int ans = INT_MIN;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if( i == 0 && j == 0 ) 
                    continue;

                int mn = INT_MAX;
                if( i > 0 ) 
                    mn = min(mn, mem[i-1][j]);
                if( j > 0 ) 
                    mn = min(mn, mem[i][j-1]);
                
                ans = max(ans, grid[i][j] - mn);
                mem[i][j] = min(grid[i][j], mn); // keep track of min seen along the path
            }
        }
        
        return ans;
    }
};



// passes 564/564 test cases, but took to long


class Solution {
private:
    int rec(vector<vector<int>>& grid, int m, int n, int i, int j, vector<vector<int>>& mem) {
        if( i == m-1 && j == n-1 )
            return -100000;
        
        if( mem[i][j] != INT_MIN )
            return mem[i][j];
        
        int ret = -100000;
        
        // we have a choice
        //     we can go to any cell below us OR 
        //     we can go to any cell right of us
        for(int k = i+1; k < m; ++k) {
            int t = grid[k][j] - grid[i][j];
            ret = max(ret, t);
            int a = t + rec(grid, m, n, k, j, mem); // if rec is negativ, we keep the best single step difference
            ret = max(ret, a);
        }
        for(int k = j+1; k < n; ++k) {
            int t = grid[i][k] - grid[i][j];
            ret = max(ret, t);
            int a = t + rec(grid, m, n, i, k, mem); // if rec is negativ, we keep the best single step difference
            ret = max(ret, a);
        }
        
        return mem[i][j] = ret;
    }
    
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // 4 <= m * n <= 1e5
        
        
        vector<vector<int>> mem(m,vector<int>(n,INT_MIN));
        rec(grid, m, n, 0, 0, mem);
        
        int ans = -100000;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                ans = max(ans, mem[i][j]);
        
        return ans;
    }
};
