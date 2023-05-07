
// 2240. Number of Ways to Buy Pens and Pencils
// https://leetcode.com/problems/number-of-ways-to-buy-pens-and-pencils/



class Solution {
public:
    long long waysToBuyPensPencils(int total, int cost1, int cost2) {
        long long ans = 0;

        for(int i = 0; i * cost1 <= total; ++i) { // pencils

            int rem_money = total - (i * cost1);
            int nbr_ways = rem_money / cost2;

            ans += nbr_ways + 1;
        }

        return ans;
    }
};
