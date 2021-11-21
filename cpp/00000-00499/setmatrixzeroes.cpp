
// 73. Set Matrix Zeroes
// https://leetcode.com/problems/set-matrix-zeroes/
// day 13 August 2021 challenge
// https://leetcode.com/explore/featured/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3888/




class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();      // rows
        int n = matrix[0].size();   // cols

        // pass1 -> get a flag, meaning an int that does not exist in row 0 or col 0
        bool f = false;
        int flag = 1;
        bool r0 = false, c0 = false;
        while( !f ) {
            f = true;
            // row 0
            for(int j = 0; j < n; ++j) {
                if( matrix[0][j] == 0 )
                    r0 = true;
                if( matrix[0][j] == flag ) {
                    ++flag;
                    f = false;
                    break;
                }
            }
            if( !f )
                continue;
            // col 0
            for(int i = 0; i < m; ++i) {
                if( matrix[i][0] == 0 )
                    c0 = true;
                if( matrix[i][0] == flag ) {
                    ++flag;
                    f = false;
                    break;
                }
            }
        }
        // cout << "flag " << flag << endl;

        // pass 2 -> set marker
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( matrix[i][j] == 0 ) {
                    matrix[0][j] = flag;
                    matrix[i][0] = flag;
                }

        // pass3 -> set rows to 0
        for(int i = 1; i < m; ++i)
            if( matrix[i][0] == flag )
                for(int j = 0; j < n; ++j)
                    matrix[i][j] = 0;

        // pass4 -> set cols to 0
        for(int j = 1; j < n; ++j)
            if( matrix[0][j] == flag )
                for(int i = 0; i < m; ++i)
                    matrix[i][j] = 0;

        // pass5 -> row 0 and col 0
        if( r0 )
            for(int j = 0; j < n; ++j)
                matrix[0][j] = 0;
        if( c0 )
            for(int i = 0; i < m; ++i)
                matrix[i][0] = 0;

    }
};
