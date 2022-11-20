
// 2218. Maximum Value of K Coins From Piles
// https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/




class Solution {
private:
    int N,K;
    int mem[2000][2000];

    int rec(vector<vector<int>>& piles, int pile, int k) {
        if( k == K || pile == N )
            return 0;

        if( mem[pile][k] != -1 )
            return mem[pile][k];

        // at each pile
        //    we can collect between 0 and K-k coins

        int ret = rec(piles,pile+1,k);

        int gain = 0;
        for(int i = 0; i < min(K-k,(int)piles[pile].size()); ++i) {
            gain += piles[pile][i];
            ret = max(ret,gain+rec(piles,pile+1,k+i+1));
        }

        return mem[pile][k] = ret;
    }

public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        N = piles.size();
        K = k;

        memset(mem,-1,sizeof mem);
        return rec(piles,0,0);
    }
};
