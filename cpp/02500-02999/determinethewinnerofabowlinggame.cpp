
// 2660. Determine the Winner of a Bowling Game
// https://leetcode.com/problems/determine-the-winner-of-a-bowling-game/



class Solution {
public:
    int isWinner(vector<int>& player1, vector<int>& player2) {
        int n = player1.size(); // player1.size() == player2.size()

        int score1 = 0, score2 = 0;
        int lastten1 = -10, lastten2 = -10;

        // play
        for(int i = 0; i < n; ++i) {
            // player 1
            score1 += lastten1 >= i - 2 ? 2 * player1[i] : player1[i];
            if( player1[i] == 10 )
                lastten1 = i;

            // player 2
            score2 += lastten2 >= i - 2 ? 2 * player2[i] : player2[i];
            if( player2[i] == 10 )
                lastten2 = i;
        }

        // return
        // 1 if the score of player 1 is more than the score of player 2,
        // 2 if the score of player 2 is more than the score of player 1, and
        // 0 in case of a draw.
        if( score1 > score2 )
            return 1;
        else if( score2 > score1 )
            return 2;
        else
            return 0;
    }
};
