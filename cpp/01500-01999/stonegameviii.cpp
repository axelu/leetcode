
// 1872. Stone Game VIII
// https://leetcode.com/problems/stone-game-viii/


class Solution {
private:
    int rec(vector<int>& stones, int n, int i, int alice, int left, int mem[][2]) {
        // alice == 1 -> alice, alice == 0 -> bob
        if( i == n )
            return 0;

        if( i == n-1 ) {
            // the current player will take 'left' and the last one
            if( alice ) {
                return left + stones[i];
            } else {
                return -(left+stones[i]);
            }
        }

        if( mem[i][alice] != -1 ) {
            return mem[i][alice];
        }


        // the current player can take [2,n-1] stones
        // "2" includes the 'left'
        int player_new = !alice;
        int sum_piles_taken = left+stones[i];

        // each player has a choice:
        //   collect the left + 1 pile OR
        //   continue collecting
        if( alice ) {
            int t1 = sum_piles_taken+rec(stones,n,i+1,player_new,sum_piles_taken,mem);
            int t2 = rec(stones,n,i+1,alice,sum_piles_taken,mem);
            return mem[i][alice] = max(t1,t2);
        } else {
            int t1 = rec(stones,n,i+1,player_new,sum_piles_taken,mem)-sum_piles_taken;
            int t2 = rec(stones,n,i+1,alice,sum_piles_taken,mem);
            return mem[i][alice] = min(t1,t2);
        }
    }

public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();  // 2 <= n <= 10^5

        if( n == 2 )        // Alice has to remove both stones
            return stones[0]+stones[1];


        int mem[n][2];memset(mem,-1,sizeof mem);

        return rec(stones,n,1,1,stones[0],mem);
    }
};
