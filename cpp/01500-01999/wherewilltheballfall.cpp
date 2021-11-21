

// 1706. Where Will the Ball Fall
// https://leetcode.com/problems/where-will-the-ball-fall/



class Solution {
private:
    // p  0/1 or 1\0; 0 above the line, 1 below the line

    int m,n;

    int rec(vector<vector<int>>& grid, int r, int c, int p, int mem[][2]) {
        if( r == m-1 && p == 1 )
                return c;

        int memIdx = r*n+c;
        if( mem[memIdx][p] != -1 )
            return mem[memIdx][p];

        int ret = -1;
        if( p == 1 ) {
            ret = rec(grid,r+1,c,0,mem);
        } else {
            if( grid[r][c] == 1 ) {     //  1 = \
                // we will go to the right
                if( c+1 < n && grid[r][c+1] == 1 )
                    ret = rec(grid,r,c+1,1,mem);
            } else {                    // -1 = /
                // we will go to the right
                if( c-1 >= 0 && grid[r][c-1] == -1 )
                    ret = rec(grid,r,c-1,1,mem);
            }
        }

        return mem[memIdx][p] = ret;
    }


public:
    vector<int> findBall(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols


        int mem[m*n][2];memset(mem,-1,sizeof mem);

        vector<int> ans(n);
        for(int j = 0; j < n; ++j)
            ans[j] = rec(grid,0,j,0,mem);
        return ans;
    }
};



