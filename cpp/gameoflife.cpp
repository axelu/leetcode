
// 289. Game of Life
// https://leetcode.com/problems/game-of-life/
// day 30 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/573/week-5-december-29th-december-31st/3586/

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        size_t m = board.size();   // rows
        size_t n = board[0].size();// columns

        int o[m][n];
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                o[i][j] = board[i][j];

        // eight possible neigboring cells
        // count the life cells
        int cnt;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                cnt = 0;

                // up
                if( i > 0 ) {
                    // left
                    if( j > 0 && o[i-1][j-1] == 1 ) ++cnt;
                    // just up
                    if( o[i-1][j] == 1 ) ++cnt;
                    // right
                    if( j < n-1 && o[i-1][j+1] == 1 ) ++cnt;
                }
                // right
                if( j < n-1 && o[i][j+1] == 1 ) ++cnt;
                // down
                if( i < m-1 ) {
                    // right
                    if( j < n-1 && o[i+1][j+1] == 1 ) ++cnt;
                    // just down
                    if( o[i+1][j] == 1 ) ++cnt;
                    // left
                    if( j > 0 && o[i+1][j-1] == 1 ) ++cnt;
                }
                // left
                if( j > 0 && o[i][j-1] == 1 ) ++cnt;

                if( o[i][j] == 1 && ( cnt < 2 || cnt > 3 ) ) {
                    board[i][j] = 0;
                } else if( o[i][j] == 0 && 3 == cnt ) {
                    board[i][j] = 1;
                }
            }
        }
    }
};
