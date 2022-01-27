
// 750. Number Of Corner Rectangles
// https://leetcode.com/problems/number-of-corner-rectangles/
// day 29 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/583/week-5-january-29th-january-31st/3620/




class Solution {
private:
    size_t N,M;
    int mem[200][200][200];

    int count(vector<vector<int>>& grid, int new_rowi, int new_rowj, int new_row) {

        // w/o mem
        /*
        int cnt = 0;
        for(int i = new_row-1; i >= 0; --i)
            if( grid[i][new_rowi] == 1 && grid[i][new_rowj] == 1 )
                ++cnt;
        */

        // w/ mem
        int cnt = 0;
        for(int i = new_row-1; i >= 0; --i) {
            if( mem[new_rowi][new_rowj][i] != 0 ) {
                cnt = mem[new_rowi][new_rowj][i];
                break;
            }
        }

        mem[new_rowi][new_rowj][new_row] = cnt+1;
        return cnt;
    }

public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        N = grid.size();    // [1, 200]
        M = grid[0].size(); // [1, 200]
        int ans = 0;
        if( N == 1 || M == 1 ) return ans;

        // init mem for row 0
        // memset(mem,0,sizeof mem);
        for(int j = 0; j < M-1; ++j) {
            if( grid[0][j] == 1 ) {
                for(int k = j+1; k < M; ++k) {
                    if( grid[0][k] == 1 ) {
                        mem[j][k][0] = 1;
                    }
                }
            }
        }

        for(int i = 1; i < N; ++i) {
            for(int j = 0; j < M-1; ++j) {
                if( grid[i][j] == 1 ) {
                   for(int k = j+1; k < M; ++k) {
                       if( grid[i][k] == 1 ) {
                           ans += count(grid,j,k,i);
                       }
                   }
                }
            }
        }

        return ans;
    }
};
