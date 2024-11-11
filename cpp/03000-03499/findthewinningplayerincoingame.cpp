
// 3222. Find the Winning Player in Coin Game
// https://leetcode.com/problems/find-the-winning-player-in-coin-game/




class Solution {
public:
    string losingPlayer(int x, int y) {
        // x coins with value 75
        // y coins with value 10

        // Alice starts

        int player = 0;
        while( true ) {

            if( x >= 1 && y >= 4 ) {
                // the current player can make a move
                x = x - 1;
                y = y - 4;
                player = !player;
            } else {
                // the current player cannot make a move
                return player == 0 ? "Bob" : "Alice";
            }
        }

        return ""; // should never get here
    }
};
