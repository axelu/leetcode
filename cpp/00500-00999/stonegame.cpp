
// 877. Stone Game
// https://leetcode.com/problems/stone-game/


class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        // piles.length is even.
        // 1 <= piles[i] <= 500
        // sum(piles) is odd.

        // player 1 Alex goes first
        // player 2 Lee
        // both play optimally = they can also look ahead

        int n = piles.size();

        int dp[n+2][n+2]; // value of the game [piles[i], ..., piles[j]]
        memset(dp, 0, sizeof(dp));

        for(int size = 1; size <= n; ++size)
            for (int i = 0, j = size - 1; j < n; ++i, ++j) {
                int turn = (j + i + n) % 2;
                if (turn == 1)
                    dp[i+1][j+1] = max(piles[i] + dp[i+2][j+1], piles[j] + dp[i+1][j]);
                else
                    dp[i+1][j+1] = min(-piles[i] + dp[i+2][j+1], -piles[j] + dp[i+1][j]);
            }

        return dp[1][n] > 0;
    }
};
