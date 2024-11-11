
// 3238. Find the Number of Winning Players
// https://leetcode.com/problems/find-the-number-of-winning-players/





class Solution {
public:
    int winningPlayerCount(int n, vector<vector<int>>& pick) {

        int ans = 0;

        vector<vector<int>> collected(n,vector<int>(11,0));
        vector<bool> winner(n,false);
        for(auto& v: pick) {
            int player = v[0];
            int color  = v[1];

            ++collected[player][color];
            if( !winner[player] && collected[player][color] > player ) {
                winner[player] = true;
                ++ans;
            }
        }

        return ans;
    }
};
