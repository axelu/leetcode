
// 3789. Minimum Cost to Acquire Requried Items
// https://leetcode.com/problems/minimum-cost-to-acquire-required-items/


class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        // naive options, but it can give us a baseline
        // one option
        //    acquire enough type1 items to meet need1 +
        //    acquire enough type2 items to meet need2
        // another option
        //    acquire enough type3 items to meet need1 and need2


        long long total_cost = 0;
        if( costBoth <= cost1 + cost2 ) {
            // we buy using costBoth till smaller need is filled
            if( need1 < need2 ) {
                total_cost = (long long)costBoth * need1;
                need2 = need2 - need1;
                need1 = 0;
            } else {
                total_cost = (long long)costBoth * need2;
                need1 = need1 - need2;
                need2 = 0;
            }
        }
        if( need1 >= 0 ) {
            total_cost += (long long)min(cost1, costBoth) * (long long)need1;
        }
        if( need2 >= 0 ) {
            total_cost += (long long)min(cost2, costBoth) * (long long)need2;
        }

        return total_cost;
    }
};
