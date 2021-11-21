
// 486. Predict the Winner
// https://leetcode.com/problems/predict-the-winner/



class Solution {
private:
    int p1score,p2score;

    int rec(vector<int>& nums, int s, int e, int player) {
        // cout << "rec s " << s << " e " << e << " player " << player << endl;
        // player == 0 -> player 1, player == 1 -> player 2
        // return 0 player1 win, return 1 player2 win

        int winner;

        if( s == e ) {
            if( player == 0 )
                p1score += nums[s];
            else
                p2score += nums[s];
            // cout << "end p1score " << p1score << " p2score " << p2score << " player " << player << endl;
            winner = p1score >= p2score ? 0 : 1;
            // backtrack
            if( player == 0 )
                p1score -= nums[s];
            else
                p2score -= nums[s];
        } else {

            int nextPlayer = !player;
            // the current player has a choice:
            // pick the 1st pile (s) or the last pile (e)

            // pick the 1st pile
            if( player == 0 )
                p1score += nums[s];
            else
                p2score += nums[s];
            int a = rec(nums,s+1,e,nextPlayer);
            // backtrack
            if( player == 0 )
                p1score -= nums[s];
            else
                p2score -= nums[s];


            // can I (current player) win making this move?
            if( player == a )
                winner = player;

            else {
                // cout << "trying other move" << endl;
                // pick the last pile
                if( player == 0 )
                    p1score += nums[e];
                else
                    p2score += nums[e];
                int b = rec(nums,s,e-1,nextPlayer);
                winner = b;
                // backtrack
                if( player == 0 )
                    p1score -= nums[e];
                else
                    p2score -= nums[e];

            }
        }
        return winner;
    }



public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return true;

        p1score = 0;
        p2score = 0;

        int t = rec(nums,0,n-1,0); // player 1 starts
        return !t;
    }
};
