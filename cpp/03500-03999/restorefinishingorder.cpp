
// 3668. Restore Finishing Order
// https://leetcode.com/problems/restore-finishing-order/



class Solution {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        int n = order.size();

        vector<int> ans(friends.size());

        int j = 0;
        for(int i = 0; i < n; ++i) {
            auto it = lower_bound(friends.begin(), friends.end(), order[i]);
            if( it != friends.end() && order[i] == *it ) {
                ans[j++] = order[i];
            }
        }

        return ans;
    }
};
