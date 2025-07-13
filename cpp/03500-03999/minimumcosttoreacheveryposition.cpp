// 3502. Minimum Cost to Reach Every Position
// https://leetcode.com/problems/minimum-cost-to-reach-every-position/


class Solution {
public:
    vector<int> minCosts(vector<int>& cost) {
        int n = cost.size();

        vector<int> ans(n);

        int mn = 101;
        for(int i = 0; i < n; ++i) {
            if( cost[i] < mn )
                mn = cost[i];
            ans[i] = mn;
        }

        return ans;
    }
};
