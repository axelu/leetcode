
// 3283. Maximum Number of Moves to Kill All Pawns
// https://leetcode.com/problems/maximum-number-of-moves-to-kill-all-pawns/





/*
 * can we precompute once all possible fewest move answers for pawn and knight positions
 * knight_x knight_y pawn_x pawn_y
 *   50       50       50     50      -> 50x50x50x50 = 6,250,000
 *   50 binary -> 110010 6 digits
 *
 * even if we could precompute those, should we?
 * we will at most have 15 pawns, so we only need to precompute
 * initial pos of knight to all pawns = 15
 *     with each move we will end up at one of the pawns positions
 * all pawns to all pawns 15 x 15 = 225
 *
 *
 */

    unordered_map<int,int> fewest_moves; // key: ki,kj,pi,pj, holding this globally


class Solution {
private:


    // directions of a chess knight
    int dirR[8] = {-2,-1, 1, 2, 2, 1,-1,-2};
    int dirC[8] = { 1, 2, 2, 1,-1,-2,-2,-1};

    int get_fewest_moves(int ki, int kj, int pi, int pj) {
        // position of night ki and kj
        // position of pawn pi and pj
        // calculates the fewest moves for the knight at ki, kj to capture the pawn at pi, pj
        // we will assume that ki,kj != pi,pj

        int key = (ki<<18) + (kj<<12) + (pi<<6) + pj;
        auto f = fewest_moves.find(key);
        if( f != fewest_moves.end() )
            return f->second;


        bool seen[50][50];memset(seen,false,sizeof seen);
        // array<int,3> number moves, i, j
        auto cmp = [](const array<int,3>& a, const array<int,3>& b) {
            return a[0] > b[0];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);

        pq.push({0,ki,kj});
        seen[ki][kj] = true;
        while( !pq.empty() ) {
            int steps = pq.top()[0];
            int i = pq.top()[1];
            int j = pq.top()[2];
            pq.pop();

            if( i == pi && j == pj ) {
                fewest_moves.insert({key,steps});
                return steps;
            }

            // do we have the answer already?
            int local_key = (i<<18) + (j<<12) + (pi<<6) + pj;
            auto local_f = fewest_moves.find(local_key);
            if( local_f != fewest_moves.end() ) {
                pq.push({steps + local_f->second, pi, pj});
                continue;
            }

            for(int k = 0; k < 8; ++k) {
                int i_new = i + dirR[k];
                if( i_new < 0 || i_new > 49 )
                    continue;

                int j_new = j + dirC[k];
                if( j_new < 0 || j_new > 49 )
                    continue;

                if( seen[i_new][j_new] )
                    continue;

                seen[i_new][j_new] = true;
                pq.push({steps+1,i_new,j_new});
            }
        }

        return -1; // we should never get here
    }

    // we can hve up to 15 pawns: 15 -> binary to capture state 32767 (111111111111111) options
    // we can have Alice or Bob's turn -> 2 options
    // we have the position of the knight -> 50x50 -> 2500 options
    // all together: 32767 * 2 * 2500 = 163,835,000 options
    // optimization:
    // our night is either at its original position of the position of the last pawn taken,
    // so it could be at most in 16 positions
    // -> 32767 * 2 * 16 = 1048544 options
    // -> 32767 * 2 * 15 = 983010 options -> so we can use a faster lookup option than unordered_map

    int mem[15][32768][2];
    int gki, gkj;

    int play(int knight, int pawns, vector<vector<int>>& positions, int player) {
        if( pawns == 0 ) // no pawns left to capture
            return 0;

        // int key = (ki<<22) + (kj<<16) + (pawns<<1) + player;
        // auto f = mem.find(key);
        // if( f != mem.end() )
        //    return f->second;

        int ki, kj;
        if( knight == -1 ) {
            // we are just starting out
            ki = gki;
            kj = gkj;
        } else {
            if( mem[knight][pawns][player] != -1 )
                return mem[knight][pawns][player];

            ki = positions[knight][0];
            kj = positions[knight][1];
        }

        // player 0 Alice 1 Bob
        // Alice wants to maximize maximize the sum of the number of moves made by both players
        // Bob wants to maximize maximize the sum of the number of moves made by both players

        int ret = player == 0 ? 0 : INT_MAX;


        // the current player can capture any remaining pawns
        int n = positions.size();
        for(int k = 0; k < n; ++k) {
            if( (pawns>>k) & 1 ) {
                // current player moves
                int a = get_fewest_moves(ki, kj, positions[k][0], positions[k][1]);
                // remaining moves
                pawns &= ~(1 << k);  // clear bit
                int b = play(k, pawns, positions, !player);
                // backtrack
                pawns |= 1 << k;     // set bit

                if( player == 0 )   // Alice
                    ret = max(ret, a + b);
                else                // Bob
                    ret = min(ret, a + b);
            }
        }

        if( knight != -1 )
            mem[knight][pawns][player] = ret;

        return ret;
    }

public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        gki = kx;
        gkj = ky;

        int n = positions.size();
        int pawns = pow(2,n)-1;
        int player = 0; // Alice starts

        memset(mem,-1,sizeof mem);

        return play(-1, pawns, positions, player);
    }
};
