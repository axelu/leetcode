
// 3393. Count Paths With the Given XOR Value
// https://leetcode.com/problems/count-paths-with-the-given-xor-value/




class Solution {
private:
    long mod = 1000000007L;

    long mem[300][300][32]; // 300x300x32 = 2880000

    long explore(vector<vector<int>>& grid, int m, int n, int i, int j, int _xor, int k) {
        if( i == m-1 && j == n-1 )
            return (_xor ^ grid[i][j]) == k;

        if( mem[i][j][_xor] != -1L )
            return mem[i][j][_xor];

        long ret = 0L;

        // go right
        if( j+1 < n )
            ret = (ret + explore(grid, m, n, i, j+1, _xor ^ grid[i][j], k)) % mod;

        // go down
        if( i+1 < m )
            ret = (ret + explore(grid, m, n, i+1, j, _xor ^ grid[i][j], k)) % mod;


        return mem[i][j][_xor] = ret;
    }


public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        memset(mem,-1,sizeof mem);
        return explore(grid, m, n, 0, 0, 0, k);
    }
};
