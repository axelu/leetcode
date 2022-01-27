
// 794. Valid Tic-Tac-Toe State
// https://leetcode.com/problems/valid-tic-tac-toe-state/





class Solution {
public:
    bool validTicTacToe(vector<string>& board) {

        // there are EIGHT winning formations
        vector<string> os_win(8);
        os_win[0] = "O  O  O  ";
        os_win[1] = " O  O  O ";
        os_win[2] = "  O  O  O";
        os_win[3] = "OOO      ";
        os_win[4] = "   OOO   ";
        os_win[5] = "      OOO";
        os_win[6] = "  O O O  ";
        os_win[7] = "O   O   O";
        vector<string> xs_win(8);
        xs_win[0] = "X  X  X  ";
        xs_win[1] = " X  X  X ";
        xs_win[2] = "  X  x  x";
        xs_win[3] = "XXX      ";
        xs_win[4] = "   XXX   ";
        xs_win[5] = "      XXX";
        xs_win[6] = "  X X X  ";
        xs_win[7] = "X   X   X";

        string os_only = "         "; int os_cnt = 0;
        string xs_only = "         "; int xs_cnt = 0;

        int strIdx;
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j) {
                strIdx = i*3+j;

                if( board[i][j] == 'O' ) {
                    os_only[strIdx] = 'O';
                    ++os_cnt;
                } else if(board[i][j] == 'X') {
                    xs_only[strIdx] = 'X';
                    ++xs_cnt;
                }
            }

        if( os_cnt && !xs_cnt )         // X starts
            return false;

        if( os_cnt > xs_cnt )           // X starts
            return false;

        // cout << "os_cnt " << os_cnt << " xs_cnt " << xs_cnt << endl;
        if( abs(os_cnt-xs_cnt) > 1 )    // players take turns
            return false;

        bool xwins = false, owins = false;

        int match;
        for(int i = 0; i < 8; ++i) {
            match = 0;
            for(int j = 0; j < 9; ++j)
               if( os_win[i][j] == 'O' && os_only[j] == 'O' ) {
                   ++match;
                   if( match == 3 ) {
                       owins = true;
                       break;
                   }
                }
            if( owins )
                break;
        }
        for(int i = 0; i < 8; ++i) {
            match = 0;
            for(int j = 0; j < 9; ++j)
               if( xs_win[i][j] == 'X' && xs_only[j] == 'X' ) {
                   ++match;
                   if( match == 3 ) {
                       xwins = true;
                       break;
                   }
                }
            if( xwins )
                break;
        }


        // cout << "os_only ::" << os_only << ":: xs_only ::" << xs_only << "::" << endl;
        if( owins && xwins )                // only one can win
            return false;

        if( xwins && xs_cnt == os_cnt )     // if player 1 wins, the game ends
            return false;

        if( owins && xs_cnt != os_cnt )     // if player 2 wins, the game ends
            return false;


        return true;
    }
};
