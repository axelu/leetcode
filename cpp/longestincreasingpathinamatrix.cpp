
// 329. Longest Increasing Path in a Matrix
// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
// day 10 April 2021 challenge
// https://leetcode.com/explore/featured/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3703/


class Solution {
private:
    int m,n;

    // directions right,down,left,up
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    int explore(vector<vector<int>>& matrix, int x, int y, int mem[]) {
        int idx = x*n+y;
        if( mem[idx] != -1 )
            return mem[idx];

        // explore all four directions
        int ret = 1;
        int x_new, y_new;
        for(int i = 0; i < 4; ++i) {
            x_new = x+dirR[i];
            if( x_new < 0 || x_new == m ) continue;
            y_new = y+dirC[i];
            if( y_new < 0 || y_new == n ) continue;

            if( matrix[x_new][y_new] > matrix[x][y] )
                ret = max(ret,explore(matrix,x_new,y_new,mem)+1);
        }

        return mem[idx] = ret;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();

        int i,j;
        int mem[m*n];
        for(i = 0; i < m*n; ++i) mem[i] = -1;

        int ans = 1;

        // every cell is a starting point
        for(i = 0; i < m; ++i)
            for(j = 0; j < n; ++j)
                ans = max(ans,explore(matrix,i,j,mem));

        return ans;
    }
};
