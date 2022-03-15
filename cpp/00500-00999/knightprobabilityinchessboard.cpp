
// 688. Knight Probability in Chessboard
// https://leetcode.com/problems/knight-probability-in-chessboard/


class Solution {
private:
    double mem[25][25][101];

    //              0  1  2  3  4  5  6  7
    int dirR[8] = {-1,-2,-2,-1, 1, 2, 2, 1};
    int dirC[8] = {-2,-1, 1, 2, 2, 1,-1,-2};

    double rec(int n, int k, int r, int c) {
        if( k == 0 )
            return 1;

        if( mem[r][c][k] != -1.0 )
            return mem[r][c][k];

        double ret = 0;

        int r_new,c_new;
        for(int i = 0; i < 8; ++i) {
            r_new = r + dirR[i];
            if( r_new < 0 || r_new >= n )
                continue;

            c_new = c + dirC[i];
            if( c_new < 0 || c_new >= n )
                continue;

            ret += 0.125 * rec(n,k-1,r_new,c_new);
        }

        return mem[r][c][k] = ret;
    }

public:
    double knightProbability(int n, int k, int row, int column) {

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                for(int o = 0; o <= k; ++o)
                    mem[i][j][o] = -1.0;

        return rec(n,k,row,column);
    }
};
