
// 2952. Minimum Number of Coins to be Added
// https://leetcode.com/problems/minimum-number-of-coins-to-be-added/





class Solution {
public:
    int minimumAddedCoins(vector<int>& coins, int target) {
        int n = coins.size();

        sort(coins.begin(),coins.end());

        int added = 0;
        int sum = 0; // summing the coins we have (and the coins we add) tells us, if we can reach the target
        for(int i = 0; i < n; ++i) {
            // if the next coin does not allow us to build sum + 1,
            // then we have a gap and need to add a coin
            while( coins[i] > sum + 1 ) {
                ++added;
                // we are adding a coin of value sum + 1,
                // because the goal is to add minimum number of coins
                // that means, we can reach      sum     +   sum + 1
                //                          ------------   -----------
                //                          existing sum + coin we add
                sum = sum + sum + 1;
            }
            // sum the current coin
            sum += coins[i];

            if( sum >= target )
                break;
        }
        // if we cannot reach target yet, then we need to add more coins
        while( sum < target ) {
            ++added;
            sum = sum + sum + 1;
        }

        return added;
    }
};
