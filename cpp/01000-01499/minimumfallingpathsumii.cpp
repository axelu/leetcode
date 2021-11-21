
// 1289. Minimum Falling Path Sum II
// https://leetcode.com/problems/minimum-falling-path-sum-ii/




class Solution {
private:
    int mem[201][201];

    int rec(vector<vector<int>>& matrix, int n, int r, int c) {
        // c is the column in the row above that we came from
        if( r == n )
            return 0;

        if( mem[r][c] != -1 )
           return mem[r][c];

        // we have choices
        int ret = INT_MAX;
        for(int i = 0; i < n; ++i) {
            if( i == c )
                continue;
            ret = min(ret,matrix[r][i]+rec(matrix,n,r+1,i));
        }

        return mem[r][c] = ret;
    }

public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size(); // n == matrix.length == matrix[i].length
        if( n == 1 )
            return grid[0][0];

        memset(mem,-1,sizeof mem);

        int ans = INT_MAX;
        for(int i = 0; i < n; ++i)
            ans = min(ans,grid[0][i]+rec(grid,n,1,i));

        return ans;

    }
};
