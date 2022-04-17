
// 1798. Maximum Number of Consecutive Values You Can Make
// https://leetcode.com/problems/maximum-number-of-consecutive-values-you-can-make/



class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(),coins.end());

        int x = 0; // the max of values we have been able to make that far
        for(int i = 0; i < coins.size(); ++i)
            if( x + 1 >= coins[i] )
                // coins[i] happens to be the next value aka x + 1 OR
                // we can already make values up to and greater coins[i]
                // as we so far were able to make all values 0 to x
                // now we can make all values up to coins[i] + x
                x = coins[i] + x;

        return x + 1; // +1 as we can make 0 by not taking any coin
    }
};
