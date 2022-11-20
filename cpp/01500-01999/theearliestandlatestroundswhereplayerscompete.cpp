
// 1900. The Earliest and Latest Rounds Where Players Compete
// https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/





class Solution {
private:
    // debug
    void printBinary(long x, int c) {
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int N;
    int _firstPlayer, _secondPlayer;
    int earliest, latest;

    void rec(int round, int curr, int next) {
        // cout << "rec round " << round << endl;
        // cout << "    current      ";printBinary(curr,N);cout << endl;
        // cout << "    next         ";printBinary(next,N);cout << endl;

        if( next == 0 && countSetBits(curr) == 1) // we have a winner
            return;

        // pair the 'outer pair' players in curr
        int left_player;        // left most bit set (second player as we count bits from the right)
        for(int i = N-1; i >= 0; --i)
            if( (curr >> i) & 1 ) {
                left_player = i;
                break;
            }
        int right_player;       // right most bit set (first player as we count bits from the right)
        for(int i = 0; i < N; ++i)
            if( (curr >> i) & 1 ) {
                right_player = i;
                break;
            }

        // cout << "    left player  " << left_player << endl;
        // cout << "    right_player " << right_player << endl;

        // firstPlayer and secondPlayer are facing each other
        if( right_player == _firstPlayer && left_player == _secondPlayer ) {
            earliest = min(earliest,round);
            latest = max(latest,round);
            return; // no point to play further
        }

        // edge case: only one player left (odd number players at begin of round)
        //            we will advance that one remaining player to the next round
        if( right_player == left_player ) {
            next |= 1 << right_player;
            rec(round+1,next,0);

            return;
        }

        // if it so happens, that left_player == secondPlayer OR right_player == firstPlayer
        // then they always win against any other player

        // remove left player and right player from current
        curr &= ~(1 << left_player);
        curr &= ~(1 << right_player);
        // determine if the current round is all done
        bool next_round = curr == 0 ? true : false;

        if( left_player == _secondPlayer || left_player == _firstPlayer) {
            // left player advances
            next |= 1 << left_player;
            if( next_round )
                rec(round+1,next,0);
            else
                rec(round,curr,next);
            return;
        } else if( right_player == _firstPlayer || right_player == _secondPlayer ) {
            // right player advances
            next |= 1 << right_player;
            if( next_round )
                rec(round+1,next,0);
            else
                rec(round,curr,next);
            return;
        }

        // left player advances
        next |= 1 << left_player;
        if( next_round )
            rec(round+1,next,0);
        else
            rec(round,curr,next);

        // right player advances
        next &= ~(1 << left_player); // backtrack
        next |= 1 << right_player;
        if( next_round )
            rec(round+1,next,0);
        else
            rec(round,curr,next);

    }

public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        N = n;
        _firstPlayer  = firstPlayer - 1;
        _secondPlayer = secondPlayer - 1;

        // 2 <= n <= 28
        // hence at most 5 rounds

        earliest = 5;
        latest   = 0;

        int curr = pow(2,n)-1;
        int next = 0;

        rec(1,curr,next);

        return {earliest,latest};
    }
};
