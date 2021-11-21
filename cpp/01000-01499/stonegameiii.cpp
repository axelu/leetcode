
// 1406. Stone Game III
// https://leetcode.com/problems/stone-game-iii/





class Solution {
private:
    int n;
    int prefix[50001];
    int mem[50000][2];

    int rec(vector<int>& stoneValue, int i, int alice) {
        // alice == 1 -> alice, alice == 0 -> bob
        if( i == n )
            return 0;

        if( mem[i][alice] != -1 )
            return mem[i][alice];

        int score = INT_MIN;

        // the current player can take 1,2 or 3 piles starting at i
        int player_new = !alice;
        int sum_piles_taken = 0, t;

        for(int x = 0; x < 3 && i+x < n; ++x) {
            sum_piles_taken += stoneValue[i+x];

            if( alice )
                t = sum_piles_taken + rec(stoneValue,i+x+1,player_new);
            else
                t = sum_piles_taken + (prefix[n]-prefix[i+x+1]-rec(stoneValue,i+x+1,player_new));

            score = max(score,t);
        }

        // as both players play optimally
        // if the current player is Alice, we return max
        // if the current player is Bob, then we return the max he would allow Alice to get

        if( alice ) {
            return mem[i][alice] = score;
            // return score;
        } else {
            return mem[i][alice] = prefix[n]-prefix[i]-score;
            // return prefix[n]-prefix[i]-score;
        }




    }

public:
    string stoneGameIII(vector<int>& stoneValue) {
        n = stoneValue.size();

        // int prefix[n+1];
        prefix[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefix[i] = prefix[i-1]+stoneValue[i-1];

        int total = prefix[n];
        // cout << "total " << total << endl;
        // if total is even, there could be a tie, otherwise
        // there cannot be a tie

        // Alice always starts
        // if Alice can win one game, she wins
        // if she can get a tie, its a tie
        // else Bob wins

        memset(mem,-1,sizeof mem);

        int a = rec(stoneValue,0,1);
        int b = total-a;
        if( a == b )
            return "Tie";
        else if( a > b )
            return "Alice";
        else
            return "Bob";
    }
};
