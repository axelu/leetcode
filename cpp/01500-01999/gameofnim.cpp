
// 1908. Game of Nim
// https://leetcode.com/problems/game-of-nim/


/*
 * we use a long to represent the state as a bitmask
 * ... | ------pile 2-------- | ------pile 1-------- | ------pile 0--------
 * ... | 20 19 18 17 16 15 14 | 13 12 11 10  9  8  7 |  6  5  4  3  2  1  0
 * if a given bit is set, that means a stone is in that pile
*/
class Solution {
private:
    void printBinary(long x) {
        for(int i = 48; i >= 0; --i) {
            if( x & (1L << i) ) {
                cout << 1;
            } else {
                cout << 0;
            }
            if( i == 42 || i == 35 || i == 28 || i == 21 || i == 14 || i == 7 )
                cout << "|";
        }
        // cout << endl;
    }

    unordered_map<long,bool> mem;

    bool play(long game, int nbr_piles, int player) {
        // cout << "play game ";printBinary(game);cout << " player " << player << endl;
        // player 0 Alice, player 1 Bob
        // return true if Alice wins, or false if Bob wins.
        if( game == 0 ) // current player loses
            return player ? true : false;

        long key = game;
        if( player )
            key |= 1L << 49; // 49th bit is player bit
        auto v = mem.find(key);
        if( v != mem.end() )
            return v->second;

        bool ret = player;

        // the current player will play optimally
        // the current player can can remove 1 to n stones
        // from any non-empty pile in one move
        for(int i = 0; i < nbr_piles; ++i) {
            long curr_game = game;
            int offset = i * 7;
            for(int j = (offset+7)-1; j >= offset; --j) {
                if( (curr_game >> j) & 1 ) {
                    curr_game &= ~(1L << j); // clear bit aka remove stone
                    bool f = play(curr_game,nbr_piles,!player);

                    if( player && !f ) {
                        ret = false;
                        break;
                    } else if( !player && f ) {
                        ret = true;
                        break;
                    }
                }
            }
            // did we break? aka did current player won?
            if( player != ret )
                break;
        }

        mem.insert({key,ret});
        return ret;
    }

public:
    bool nimGame(vector<int>& piles) {
        int nbr_piles = piles.size();

        long game = 0;
        // initialize the game
        for(int i = 0; i < nbr_piles; ++i) {
            int offset = i * 7;
            for(int j = 0; j < piles[i]; ++j)
               game |= 1L << (offset+j);
        }

        // Alice starts
        return play(game,nbr_piles,0);
    }
};
