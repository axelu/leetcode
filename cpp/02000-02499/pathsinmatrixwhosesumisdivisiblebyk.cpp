
// 2435. Paths in Matrix Whose Sum Is Divisible by K
// https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/



class Solution {
private:
    long mod = 1000000007;

    int m,n,k;

    long rec(int i, int j, int sum, const vector<vector<int>>& grid,
             vector<vector<vector<long>>>& mem) {
        if( i == m-1 && j == n-1 )
            return (sum+grid[i][j]) % k == 0 ? 1 : 0;

        if( mem[i][j][sum] != -1 )
            return mem[i][j][sum];

        // we have a choice to go down or right

        long ret = 0;

        int rem = (sum + grid[i][j]) % k;

        // down
        if( i+1 != m )
            ret = (ret + rec(i+1,j,rem,grid,mem)) % mod;
        // right
        if( j+1 != n )
            ret = (ret + rec(i,j+1,rem,grid,mem)) % mod;

        return mem[i][j][sum] = ret;
    }
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols
        this->k = k;

        vector<vector<vector<long>>> mem(m,vector<vector<long>>(n,vector<long>(k,-1)));

        return rec(0,0,0,grid,mem);
    }
};
