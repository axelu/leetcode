
// 1690. Stone Game VII
// https://leetcode.com/problems/stone-game-vii/
// day 11 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/604/week-2-june-8th-june-14th/3775/




class Solution {
private:
    int n;

    int rec(int mem[], int prefixSum[], int l, int r, int player) {

        if( l == r )
            return 0;

        if( mem[l*n+r] != INT_MAX)
            return mem[l*n+r];

        // at each turn the player has the option of
        // taking the stone at index l or r

        // score when taking the stone at index l
        int scoreRemoveFirst = prefixSum[r+1] - prefixSum[l+1];
        int scoreRemoveLast  = prefixSum[r]   - prefixSum[l];

        int ans;
        if( player == 0 ) { // Alice
            int resultRemoveFirst = rec(mem,prefixSum,l+1,r,1) + scoreRemoveFirst;
            int resultRemoveLast  = rec(mem,prefixSum,l,r-1,1) + scoreRemoveLast;
            // play optimally - maximize score difference
            ans = max(resultRemoveFirst,resultRemoveLast);

        } else {            // Bob
            int resultRemoveFirst = rec(mem,prefixSum,l+1,r,0) - scoreRemoveFirst;
            int resultRemoveLast  = rec(mem,prefixSum,l,r-1,0) - scoreRemoveLast;
            // play optimally - minimize score difference
            ans = min(resultRemoveFirst,resultRemoveLast);
        }

        return mem[l*n+r] = ans;
    }

public:
    int stoneGameVII(vector<int> &stones) {
        n = stones.size();

        int prefixSum[n+1];prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + stones[i];

        int mem[n*n];
        for(int i = 0; i < n*n; ++i)
                mem[i] = INT_MAX;

        // player 0 Alice start
        // player 1 Bob

        return abs(rec(mem,prefixSum,0,n-1,0));
    }
};
