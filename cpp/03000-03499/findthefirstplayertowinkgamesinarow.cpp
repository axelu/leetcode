
// 3175. Find The First Player to win K Games in a Row
// https://leetcode.com/problems/find-the-first-player-to-win-k-games-in-a-row/





class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int n = skills.size(); // 2 <= n <= 1e5

        // 1 <= k <= 1e9
        // brute force aka simulation will be TLE because k can be so big
        // but the moment the player is the player with the highest skill level, he will always win
        // no matter how many rounds are left

        int mx_skill = *max_element(skills.begin(), skills.end());

        queue<int> q;
        for(int i = 1; i < n; ++i)
            q.push(i);

        int wins[n];memset(wins,0,sizeof wins);

        int player1 = 0;
        while( true ) {
            int player2 = q.front();
            q.pop();

            int skill1 = skills[player1];
            if( skill1 == mx_skill )        // early exit
                return player1;

            int skill2 = skills[player2];

            if( skill1 > skill2 ) {
                ++wins[player1];
                if( wins[player1] == k )
                    return player1;
                q.push(player2);

            } else { // skill2 > skill1
                ++wins[player2];
                if( wins[player2] == k )
                    return player2;

                q.push(player1);
                player1 = player2;
            }
        }

        return -1; // should never get here
    }
};
