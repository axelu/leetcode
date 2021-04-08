
// 885. Spiral Matrix III
// https://leetcode.com/problems/spiral-matrix-iii/



class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        vector<vector<int>> ans(R*C,vector<int>(2));
        if( R == 1 && C == 1) {
            ans[0] = {0,0};
            return ans;
        }

        // observation:
        //    we walk x steps in a given direction and then change direction,
        //    that repeats 2 times, and then the number of steps increases by one

        int dir = 0; // 0 right, 1 down, 2 left, 3 up
        int k = 0, i = r0, j = c0;

        int stps = 1; // steps to take in a given direction
        int csts = 0; // current step counter
        int rept = 0; // current repetition counter

        while(k < R*C) {
            // cout << i << " " << j << endl;
            if( i >=0 && i < R && j >=0 && j < C ) {
                // inside the matrix
                ans[k] = {i,j};
                ++k;
            }

            bool changedDir = false;
            if( 0 == dir ) {
                // right
                if( csts < stps ) {
                    ++j;    // advance column
                    ++csts;
                } else {
                    ++i;     // advance row
                    dir = 1; // change direction
                    changedDir = true;
                }
            } else if( 1 == dir ) {
                // down
                if( csts < stps ) {
                    ++i;    // advance row
                    ++csts;
                } else {
                    --j;     // reduce column
                    dir = 2; // change direction
                    changedDir = true;
                }
            } else if( 2 == dir ) {
                // left
                if( csts < stps ) {
                    --j;    // reduce column
                    ++csts;
                } else {
                    --i;     // reduce row
                    dir = 3; // change direction
                    changedDir = true;
                }
            } else if( 3 == dir ) {
                // up
                if( csts < stps ) {
                    --i;    // reduce row
                    ++csts;
                } else {
                    ++j;     // advance column
                    dir = 0; // change direction
                    changedDir = true;
                }
            }

            if( changedDir ) {
                // reset steps and repetition
                csts = 1;
                ++rept;
                if( rept == 2 ) {
                    rept = 0;
                    ++stps;
                }
            }
        }
        return ans;
    }
};
