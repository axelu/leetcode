
// 2510. Check if There is a Path With Equal Number of 0's And 1's
// https://leetcode.com/problems/check-if-there-is-a-path-with-equal-number-of-0s-and-1s/




class Solution {
private:
    vector<vector<vector<int>>> mem;

    bool rec(vector<vector<int>>& grid, int m, int n, int i, int j, int d) {
        // cout << "rec i " << i << " j " << j << " d " << d << endl;
        // d == difference between the number of 0’s and the number of 1’s that we visited so far

        if( i == m || j == n )
            return false;

        int d_new = d;
        if( grid[i][j] == 1 )
            ++d_new;
        else
            --d_new;

        if( i == m-1 && j == n-1 )
            return d_new == m+n+1;

        if( mem[i][j][d] != -1 )
            return mem[i][j][d];

        bool f = false;

        // go down
        f = rec(grid,m,n,i+1,j,d_new);

        // go right
        if( !f )
            f = rec(grid,m,n,i,j+1,d_new);

        return mem[i][j][d] = f;
    }
public:
    bool isThereAPath(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        mem = vector<vector<vector<int>>>(m,vector<vector<int>>(n,vector<int>((m+n+1)*2,-1)));

        return rec(grid,m,n,0,0,m+n+1);
    }
};
