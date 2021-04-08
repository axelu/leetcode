
// 1025. Divisor Game
// https://leetcode.com/problems/divisor-game/



class Solution {
public:
    bool divisorGame(int N) {
        // Alice starts first, so her turn is on move 0,2,4,...

        int move = 0;
        int i = 1;
        while(i<N) {
            if( N % i == 0 ) {
                ++move;
                N = N-i;
                i = 1;
            } else {
                ++i;
            }
        }

        return move % 2;
    }
}
