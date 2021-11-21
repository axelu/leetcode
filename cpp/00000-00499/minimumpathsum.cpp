
// 64. Minimum Path Sum
// https://leetcode.com/problems/minimum-path-sum/





class Solution {
private:
    int m,n;

    // directions right,down
    int dirR[2] = {0,1};
    int dirC[2] = {1,0};

    int rec(vector<vector<int>>& grid, int i, int j, int seen[]) {
        if( i == m-1 && j == n-1 )
            return grid[i][j];

        int seenIdx = i*n+j;
        if( seen[seenIdx] != -1 )
            return seen[seenIdx];

        int ret = INT_MAX;
        int i_new,j_new,t;
        for(int k = 0; k < 2; ++k) {
            i_new = i + dirR[k];
            if( i_new == m )
                continue;
            j_new = j + dirC[k];
            if( j_new == n )
                continue;

            t = rec(grid,i_new,j_new,seen);
            ret = min(ret,t);
        }

        return seen[seenIdx] = ret + grid[i][j];
    }


public:
    int minPathSum(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int seen[m*n];memset(seen,-1,sizeof seen);
        return rec(grid,0,0,seen);
    }
};
