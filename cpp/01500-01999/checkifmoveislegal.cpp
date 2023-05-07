
// 1958. Check if Move is Legal
// https://leetcode.com/problems/check-if-move-is-legal/



class Solution {
private:
    bool checkMove(vector<vector<char>>& board, int i, int j, int i_incr, int j_incr, char color) {
        int steps = 0;
        i = i + i_incr;
        j = j + j_incr;
        while( i != -1 && i != 8 && j != -1 && j != 8 ) {
            if( board[i][j] == '.' )
                break;

            ++steps;
            if( steps >= 2 && board[i][j] == color )
                return true;

            if( board[i][j] == color )
                break;

            i = i + i_incr;
            j = j + j_incr;
        }

        return false;
    }

public:
    bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color) {
        // board[rMove][cMove] == '.'

        // right up
        if( checkMove(board, rMove, cMove, -1, 1, color) )
            return true;
        // right
        if( checkMove(board, rMove, cMove, 0, 1, color) )
            return true;
        // right down
        if( checkMove(board, rMove, cMove, 1, 1, color) )
            return true;
        // down
        if( checkMove(board, rMove, cMove, 1, 0, color) )
            return true;
        // left down
        if( checkMove(board, rMove, cMove, 1, -1, color) )
            return true;
        // left
        if( checkMove(board, rMove, cMove, 0, -1, color) )
            return true;
        // left up
        if( checkMove(board, rMove, cMove, -1, -1, color) )
            return true;
        // up
        if( checkMove(board, rMove, cMove, -1, 0, color) )
            return true;

        return false;
    }
};
