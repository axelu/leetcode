
// 3001. Minimum Moves to Capture The Queen
// https://leetcode.com/problems/minimum-moves-to-capture-the-queen/





char board[8][8] = {{'w','b','w','b','w','b','w','b'},
                    {'b','w','b','w','b','w','b','w'},
                    {'w','b','w','b','w','b','w','b'},
                    {'b','w','b','w','b','w','b','w'},
                    {'w','b','w','b','w','b','w','b'},
                    {'b','w','b','w','b','w','b','w'},
                    {'w','b','w','b','w','b','w','b'},
                    {'b','w','b','w','b','w','b','w'}};

class Solution {
private:
    char color(int i, int j) {
        return board[i-1][j-1];
    }

    // directions  UR DR DL UL
    int dirR[4] = {-1, 1, 1,-1};
    int dirC[4] = { 1, 1,-1,-1};

    bool can_bishop_take_queen_in_one_move(int a, int b, int c, int d, int e, int f) {
        for(int k = 0; k < 4; ++k) {
            int c_new = c;
            int d_new = d;
            while( true ) {
                c_new = c_new + dirR[k];
                if( c_new == 0 || c_new == 9 )
                    break;
                d_new = d_new + dirC[k];
                if( d_new == 0 || d_new == 9 )
                    break;

                // we cannot jump over the rook
                if( c_new == a && d_new == b )
                    break;

                if( c_new == e && d_new == f )
                    return true;
            }
        }

        return false;
    }

    bool can_rook_take_queen_in_one_move(int a, int b, int c, int d, int e, int f) {

        if( a == e ) {
            // is the bishop in the way?
            if( c != a )
                return true;

            if( b > f )
                swap(b,f);

            if( d < b || f < d )
                return true;

        } else if( b == f ) {
            // is the bishop in the way?
            if( d != b )
                return true;

            if( a > e )
                swap(a,e);

            if( c < a || e < c )
                return true;
        }

        return false;
    }


public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        // 1-indexed 8 x 8 chessboard containing 3 pieces
        // (a, b) denotes the position of the white rook.
        // (c, d) denotes the position of the white bishop.
        // (e, f) denotes the position of the black queen.
        // The queen does not move

        char color_queen = color(e,f);
        char color_bishop = color(c,d);
        if( (color_bishop == color_queen && can_bishop_take_queen_in_one_move(a,b,c,d,e,f)) ||
            can_rook_take_queen_in_one_move(a,b,c,d,e,f) )
            return 1;

        return 2;;
    }
};
