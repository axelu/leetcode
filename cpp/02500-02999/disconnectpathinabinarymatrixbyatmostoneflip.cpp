
// 2556. Disconnect Path in a Binary Matrix by at Most One Flip
// https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/




class Solution {
private:
    int m,n;

    // DFS
    bool dfs_o(vector<vector<int>>& grid, int i, int j, bool path[], bool seen[]) {
        if( i == m-1 && j == n-1 )
            return true;

        int u = i * n + j;
        seen[u] = true;

        bool ret = false;

        // go right
        if( j+1 < n && grid[i][j+1] == 1 && !seen[i*n + (j+1)] )
            ret = dfs_o(grid,i,j+1,path,seen);

        // go down
        if( !ret && i+1 < m && grid[i+1][j] == 1 && !seen[(i+1)*n + j] )
            ret = dfs_o(grid,i+1,j,path,seen);

        if( ret )
            path[u] = true;

        return ret;
    }

    // DFS
    bool dfs_t(vector<vector<int>>& grid, int i, int j, bool path[], bool seen[]) {
        if( i == m-1 && j == n-1 )
            return true;

        int u = i * n + j;
        seen[u] = true;

        bool ret = false;

        // go right
        if( j+1 < n && grid[i][j+1] == 1 && !seen[i*n + (j+1)] && !path[i*n + (j+1)])
            ret = dfs_t(grid,i,j+1,path,seen);

        // go down
        if( !ret && i+1 < m && grid[i+1][j] == 1 && !seen[(i+1)*n + j] && !path[(i+1)*n + j])
            ret = dfs_t(grid,i+1,j,path,seen);

        return ret;
    }



public:
    bool isPossibleToCutPath(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols

        if( m == 1 && n == 1 )
            return false;

        int g_sz = m*n;

        // establish if there is a path at all, let it be our original path
        bool originalpath[g_sz];memset(originalpath,false,sizeof originalpath);
        bool seen[g_sz];memset(seen,false,sizeof seen);
        if( !dfs_o(grid,0,0,originalpath,seen) )
            return true;

        // if there is another path that does not traverse any of the same nodes
        // as our originalpath except [0,0] and [m-1,n-1], then the answer is false
        memset(seen,false,sizeof seen);
        if( dfs_t(grid,0,0,originalpath,seen) )
            return false;

        return true;
    }
};
