
// 1275. Find Winner on a Tic Tac Toe Game
// https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/


class Solution {
public:
    string tictactoe(vector<vector<int>>& moves) {
        // setup board
        char board[3][3];
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                board[i][j] = ' ';

        // play the game, player A starts and uses X's, player B uses O's
        char player = 'A';
        auto n = moves.size();
        char c;
        for(int i = 0; i < n; ++i) {
            c = player == 'A' ? 'X' : 'O';
            board[moves[i][0]][moves[i][1]] = c;
            player = player == 'A' ? 'B' : 'A';
        }

        // checking rows for winner
        for(int i = 0; i < 3; ++i)
            if( board[i][0] == board[i][1] && board[i][1] == board[i][2] )
                if( board[i][0] != ' ' )
                    return board[i][0] == 'X' ? "A" : "B";

        // checking columns for winner
        for(int j = 0; j < 3; ++j)
            if( board[0][j] == board[1][j] && board[1][j] == board[2][j] )
                if( board[0][j] != ' ' )
                    return board[0][j] == 'X' ? "A" : "B";

        // checking diagonals for winner
        // 0,0 - 1,1 - 2,2
        if( board[0][0] == board[1][1] && board[1][1] == board[2][2] )
            if( board[0][0] != ' ' )
                return board[0][0] == 'X' ? "A" : "B";
        // 0,2 - 1,1 - 2,0
        if( board[0][2] == board[1][1] && board[1][1] == board[2][0] )
            if( board[0][2] != ' ' )
                return board[0][2] == 'X' ? "A" : "B";

        // no winner, is it pending?
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                if( board[i][j] == ' ' ) return "Pending";

        // it is a Draw
        return "Draw";
    }
};
