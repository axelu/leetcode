
// 1140. Stone Game II
// https://leetcode.com/problems/stone-game-ii/




class Solution {
private:
    int prefix[101];
    int mem[101][202][2];

    int rec(vector<int>& piles, int n, int i, int m, int alice) {
        // alice == 1 -> alice, alice == 0 -> bob
        if( i == n )
            return 0;

        if( mem[i][m][alice] != -1 )
           return mem[i][m][alice];

        int score = 0;

        // the current player can take 1 <= x <= 2m piles starting at i
        int player_new = !alice;
        int sum_piles_taken = 0, t;

        for(int x = 1; x <= 2*m && i+x-1 < n; ++x) {
            sum_piles_taken += piles[i+x-1];

            if( alice )
                t = sum_piles_taken + rec(piles,n,i+x,max(x,m),player_new);
            else
                t = sum_piles_taken + (prefix[n]-prefix[i+x]-rec(piles,n,i+x,max(x,m),player_new));

            score = max(score,t);
        }


        // as both players play optimally
        // if the current player is Alice, we return max
        // if the current player is Bob, then we return the max he would allow Alice to get

        if( alice ) {
            return mem[i][m][1] = score;
            // return score;
        } else {
            return mem[i][m][0] = prefix[n]-prefix[i]-score;
            // return prefix[n]-prefix[i]-score;
        }

    }


public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // int prefix[n+1];
        prefix[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefix[i] = prefix[i-1]+piles[i-1];


        memset(mem,-1,sizeof mem);
        return rec(piles,n,0,1,1);
    }
};
