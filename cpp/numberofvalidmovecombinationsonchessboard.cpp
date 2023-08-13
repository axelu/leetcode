






class Solution {
private:
    int n;

    // rook        -----------
    // queen       -----------------------
    // bishop                 ------------
    // directions   D  U  R  L DR DL UR UL
    //              0  1  2  3  4  5  6  7
    int dirR[8] = { 1,-1, 0, 0, 1, 1,-1,-1};
    int dirC[8] = { 0, 0, 1,-1, 1,-1, 1,-1};

    int rec(vector<string>& pieces, vector<vector<int>>& positions, bool board[8][8][8], int piece) {
        // cout << "rec piece " << piece << endl;
        if( piece == pieces.size() )
            return 1;

        int dirmn, dirmx;
        if( pieces[piece] == "rook" ) {
            dirmn = 0;
            dirmx = 3;
        } else if( pieces[piece] == "queen" ) {
            dirmn = 0;
            dirmx = 7;
        } else { // "bishop"
            dirmn = 4;
            dirmx = 7;
        }

        int ret = 0;

        int i = positions[piece][0] - 1;
        int j = positions[piece][1] - 1;


        // first we move
        for(int k = dirmn; k <= dirmx; ++k) { // for each direction
            int i_new = i;
            int j_new = j;

            int t = 0;  // round
            while( true ) {
                ++t;

                i_new = i_new + dirR[k];
                j_new = j_new + dirC[k];

                // are we still on the board ?
                // is some other piece before us already occupying this cell at the same time?
                if( i_new < 0 || i_new > 7 ||
                    j_new < 0 || j_new > 7 ||
                    board[i_new][j_new][t] ) {

                    // backtrack the path of our piece
                    --t;
                    while( t >= 1 ) {
                        i_new = i_new - dirR[k];
                        j_new = j_new - dirC[k];
                        board[i_new][j_new][t] = false;
                        --t;
                    }
                    break;
                }

                board[i_new][j_new][t] = true;

                // does our path end here?
                bool f = true;
                for(int fr = t + 1; fr < 8; ++fr) {
                    if( board[i_new][j_new][fr] ) {
                        f = false;
                        break;
                    }
                }
                if( !f )
                    continue;

                // mark us as occupying this cell for future rounds
                for(int fr = t + 1; fr < 8; ++fr)
                    board[i_new][j_new][fr] = true;

                ret += rec(pieces,positions,board,piece+1);

                // backtrack
                for(int fr = t + 1; fr < 8; ++fr)
                    board[i_new][j_new][fr] = false;
            }
        }

        // our initial position is our final destination
        bool f = true;
        // if this cell is already occupied in future rounds,
        // then this is not a valid combination
        for(int t = 1; t < 8; ++t)
            if( board[i][j][t] ) {
                f = false;
                break;
            }
        if( !f )
            return ret;

        // mark us as occupying this cell for all future rounds
        for(int t = 1; t < 8; ++t)
            board[i][j][t] = true;

        ret += rec(pieces,positions,board,piece+1);

        // backtrack
        for(int t = 1; t < 8; ++t)
            board[i][j][t] = false;

        return ret;
    }

public:
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        n = pieces.size(); // pieces.size() = positions.size()

        // brute force
        bool board[8][8][8];memset(board,false,sizeof board); // i,j,round
        return rec(pieces,positions,board,0);
    }
};
