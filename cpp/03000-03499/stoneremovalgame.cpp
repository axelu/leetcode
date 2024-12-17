
// 3360. Stone Removal Game
// https://leetcode.com/problems/stone-removal-game/




class Solution {
public:
    bool canAliceWin(int n) {

        int to_be_removed = 10;

        // Alice starts
        int player = 0; // Alice 0 Bob 1

        while( true ) {
            if( to_be_removed > n ) {
                // the current player looses
                return player == 1;
            }
            // setup next round
            n -= to_be_removed;
            to_be_removed -= 1;
            player = !player;
        }


    }
};
