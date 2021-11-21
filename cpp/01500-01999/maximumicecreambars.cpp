
// 1833. Maximum Ice Cream Bars
// https://leetcode.com/problems/maximum-ice-cream-bars/


class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(),costs.end());
        int ans = 0, sum = 0;
        for(int i : costs) {
            sum += i;
            if( sum <= coins ) ++ans;
            if( sum >= coins ) break;
        }
        return ans;
    }
};
