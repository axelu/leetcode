
// 348. Design Tic-Tac-Toe
// https://leetcode.com/problems/design-tic-tac-toe/
// day 22 May 2021 challenge bonus question
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/601/week-4-may-22nd-may-28th/3751/




class TicTacToe {
private:
    int N;
    int r1[101];
    int c1[101];
    int d1;     // diagonal left top to right bottom
    int d1r;    // diagonal right top to left bootom
    int r2[101];
    int c2[101];
    int d2;     // diagonal left top to right bottom
    int d2r;    // diagonal right top to left bootom
    int winner;
public:
    /** Initialize your data structure here. */
    TicTacToe(int n) {
        N = n;
        memset(r1,0,sizeof r1);
        memset(c1,0,sizeof c1);
        d1 = 0;
        d1r = 0;
        memset(r2,0,sizeof r2);
        memset(c2,0,sizeof c2);
        d2 = 0;
        d2r = 0;
        winner = 0;
    }

    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        if( player == 1 ) {
            ++r1[row];
            if( r1[row] == N && winner == 0 ) winner = 1;
            ++c1[col];
            if( c1[col] == N && winner == 0 ) winner = 1;
            if( row == col ) {
                ++d1;
                if( d1 == N && winner == 0 ) winner = 1;
            }
            if( row+col == N-1 ) {
                ++d1r;
                if( d1r == N && winner == 0 ) winner = 1;
            }


        } else {
            ++r2[row];
            if( r2[row] == N && winner == 0 ) winner = 2;
            ++c2[col];
            if( c2[col] == N && winner == 0 ) winner = 2;
            if( row == col ) {
                ++d2;
                if( d2 == N && winner == 0 ) winner = 2;
            }
            if( row+col == N-1 ) {
                ++d2r;
                if( d2r == N && winner == 0 ) winner = 2;
            }
        }
        return winner;
    }
};
