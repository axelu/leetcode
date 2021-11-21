
// 294. Flip Game II
// https://leetcode.com/problems/flip-game-ii/



class Solution {
private:
    size_t N;
    map<pair<string,int>,int> mem;

    int play(string& s, int player) {

        // did we already have this state?
        auto f = mem.find({s,player});
        if( f != mem.end() ) return f->second;

        int otherPlayer = player == 1 ? 2 : 1;

        for(int i = 1; i < N; ++i) {
            if( s[i-1] == '+' && s[i] == '+' ) {
                // new state of game
                s[i-1] = '-';
                s[i] = '-';
                // play
                int winner = play(s,otherPlayer);
                // restore state of game
                s[i-1] = '+';
                s[i] = '+';
                if( winner == player ) {
                    // found a move in which we win
                    mem.insert({{s,player},player});
                    return player;
                }
            }
        }

        // we either couldn't make a move, meaning the other player wins
        // or if we were able to make a move, whatever move we made, the other player wins
        mem.insert({{s,player},otherPlayer});
        return otherPlayer;
    }

public:
    bool canWin(string s) {
        N = s.size();
        if( N < 2 ) return false;

        // player 1 and 2, player 1 starts the game

        for(int i = 1; i < N; ++i) {
            if( s[i-1] == '+' && s[i] == '+' ) {
                // new state of game
                s[i-1] = '-';
                s[i] = '-';
                // play
                int winner = play(s,2);
                if( winner == 1 ) return true;
                // restore state of game
                s[i-1] = '+';
                s[i] = '+';
            }
        }

        return false;
    }
};
