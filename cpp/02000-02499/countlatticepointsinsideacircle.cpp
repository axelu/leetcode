
// 2249. Count Lattice Points Inside a Circle
// https://leetcode.com/problems/count-lattice-points-inside-a-circle/



class Solution {
public:
    int countLatticePoints(vector<vector<int>>& circles) {
        // int seen[201][201];memset(seen,0,sizeof seen);
        vector<vector<int>> seen(201,vector<int>(201,0));

        int ans = 0;

        for(auto& v: circles) {
            int x = v[0];
            int y = v[1];
            int r = v[2];

            // lets first add all points we know are covered
            // horizontal
            for(int j = x-r; j <= x+r; ++j)
                if( seen[y][j] == 0 ) {
                    seen[y][j] = 1;
                    ++ans;
                }
            // vertical
            for(int i = y-r; i <= y+r; ++i)
                if( seen[i][x] == 0 ) {
                    seen[i][x] = 1;
                    ++ans;
                }

            // let quadrant0 be the quarter circle right top of its center x,y
            // horizontal in quadrant 0: sweep for all y < i < y+r and x < j < x+r
            // then extrapolate to the remaining quadrants

            for(int j = 1; j < r; ++j) {        // y
                for(int i = 1; i < r; ++i) {    // x
                    if( i*i + j*j <= r*r ) {
                        // quadrant 0
                        if( seen[y+j][x+i] == 0 ) {
                            seen[y+j][x+i] = 1;
                            ++ans;
                        }
                        // quadrant 1
                        if( seen[y+j][x-i] == 0 ) {
                            seen[y+j][x-i] = 1;
                            ++ans;
                        }
                        // quadrant 2
                        if( seen[y-j][x-i] == 0 ) {
                            seen[y-j][x-i] = 1;
                            ++ans;
                        }
                        // quadrant 3
                        if( seen[y-j][x+i] == 0 ) {
                            seen[y-j][x+i] = 1;
                            ++ans;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
