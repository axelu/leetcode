
// 999. Available Captures for Rook
// https://leetcode.com/problems/available-captures-for-rook/


class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        // 'R' -> white rook
        // '.' -> empty
        // 'B' -> white bishop
        // 'p' -> black pawn

        // locate the rook
        int rr,rc;
        for(int i = 0; i < 8; ++i)
            for(int j = 0; j < 8; ++j)
                if( board[i][j] == 'R' ) {
                    rr = i;
                    rc = j;
                }

        int ans = 0;
        // up
        for(int i = rr-1; i >= 0; --i) {
            if( board[i][rc] == 'p' ) {++ans;break;}
            if( board[i][rc] == 'B' ) break;
        }
        // down
        for(int i = rr+1; i < 8; ++i) {
            if( board[i][rc] == 'p' ) {++ans;break;}
            if( board[i][rc] == 'B' ) break;
        }
        // left
        for(int j = rc-1; j >= 0; --j) {
            if( board[rr][j] == 'p' ) {++ans;break;}
            if( board[rr][j] == 'B' ) break;
        }
        // right
        for(int j = rc+1; j < 8; ++j) {
            if( board[rr][j] == 'p' ) {++ans;break;}
            if( board[rr][j] == 'B' ) break;
        }

        return ans;
    }
};
