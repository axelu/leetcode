
// 2410. Maximum Matching of Players With Trainers
// https://leetcode.com/problems/maximum-matching-of-players-with-trainers/




class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(),players.end(),greater<int>());
        sort(trainers.begin(),trainers.end(),greater<int>());

        int players_sz = players.size();
        int trainers_sz = trainers.size();

        int matched = 0;

        int players_idx = 0;
        int trainers_idx = 0;
        while( players_idx < players_sz && trainers_idx < trainers_sz ) {
            // we will match the current player with the 1st trainer where
            // trainers[trainers_idx] >= players[players_idx]

            if( trainers[trainers_idx] >= players[players_idx] ) {
                ++matched;
                ++players_idx;
                ++trainers_idx;
                continue;
            }

            ++players_idx;
        }

        return matched;
    }
};
