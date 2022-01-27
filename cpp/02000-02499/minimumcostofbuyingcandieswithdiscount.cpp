
// 2144. Minimum Cost of Buying Candies With Discount
// https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/



class Solution {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.begin(),cost.end());
        int n = cost.size();
        int ans = 0;
        for(int i = n-1; i >= 0; --i) {
            if( i <= 1 ) {
                ans += cost[i];
                if( i == 1 )
                    ans += cost[0];
                break;
            }
            ans += cost[i];
            --i;
            ans += cost[i];
            --i;
        }

        return ans;
    }
};
