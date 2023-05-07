
// 1040. Moving Stones Until Consecutive II
// https://leetcode.com/problems/moving-stones-until-consecutive-ii/



class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        sort(stones.begin(),stones.end());
        int n = stones.size(); // number of stones !!!

        // max moves
        // we can either move the left endstone, or the right endstone (one move) to get started
        // then we move through the all free spaces one by one
        // the problem is when there is a gap between the endstone and the next stone
        // either from the left or from the right
        // we need to start with the endstone that has the smaller gap and move that endstong into
        // the larger gap
        int lft_gap = stones[n-1] - stones[1] - n + 1;
        int rgt_gap = stones[n-2] -  stones[0] - n + 1;
        int mx_moves = max(lft_gap,rgt_gap) + 1; // +1 for moving the endstone

        // min moves
        // we need to find the longest number of already consecutive stones
        // and move all other stones close to them
        // sliding window length has to be <= number of stones
        // nbr of minimum moves is n - nbr of stones in the largest sliding window
        int mn_moves = n;
        int i = 0;                                          // left index
        for(int j = 0; j < n; ++j) {                        // right index

            int window_length = stones[j] - stones[i] + 1;  // size of our window

            // shrink the window till there is no gap inside our window
            while( window_length > n ) {
               ++i;
               window_length = stones[j] - stones[i] + 1;
            }
            int l = j - i + 1;                              // stones in our window

            // edge case
            // if number of stones in window and window size is n-1
            // it will take two moves
            // example
            // 0123456789
            // xxxxxxx  x  => 2 moves
            // xxxxxxxx x  => 1 move
            if( window_length == n-1 && l == n-1 )
                mn_moves = min(mn_moves,2);
            else
                mn_moves = min(mn_moves,n-l);
        }

        // only valid invariant: mn_moves <= mx_moves
        return {mn_moves,mx_moves};
    }
};
