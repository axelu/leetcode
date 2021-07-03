
// 576. Out of Boundary Paths
// https://leetcode.com/problems/out-of-boundary-paths/
// day 24 June 2021 challenge
// https://leetcode.com/explore/featured/card/june-leetcoding-challenge-2021/606/week-4-june-22nd-june-28th/3790/





class Solution {
private:
    int MOD = 1000000007;

    int mem[50][50][51];

    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    long _findPaths(int m, int n, int remMove, int i, int j) {

        if( i < 0 || i >= m || j < 0 || j >= n )
            return 1;

        if( remMove == 0 )
            return 0;

        if( mem[i][j][remMove] != -1 )
            return mem[i][j][remMove];

        // explore all four directions
        long ans = 0;
        long t = 0;
        int i_new,j_new;
        for(int k = 0; k < 4; ++k) {
            i_new = i + dirR[k];
            j_new = j + dirC[k];
            t = _findPaths(m,n,remMove-1,i_new,j_new);
            ans = (ans + t) % MOD;
        }
        return mem[i][j][remMove] = ans;
    }

public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                for(int k = 0; k <= maxMove; ++k)
                mem[i][j][k] = -1;

        return _findPaths(m,n,maxMove,startRow,startColumn);
    }
};
