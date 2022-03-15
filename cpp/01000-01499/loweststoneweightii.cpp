
// 1049. Last Stone Weight II
// https://leetcode.com/problems/last-stone-weight-ii/



class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        if( n == 1 )
            return stones[0];

        unordered_set<int> dp[2];
        dp[0] = {stones[0],-stones[0]};
        for(int i = 1; i < n; ++i) {
            if( i % 2 ) {
                for(auto it = dp[0].begin(); it != dp[0].end(); ++it) {
                    dp[1].insert(  *it  + stones[i]);
                    dp[1].insert(-(*it) + stones[i]);
                    dp[1].insert(  *it  - stones[i]);
                    dp[1].insert(-(*it) - stones[i]);
                }
                dp[0].clear();
            } else {
                for(auto it = dp[1].begin(); it != dp[1].end(); ++it) {
                    dp[0].insert(  *it  + stones[i]);
                    dp[0].insert(-(*it) + stones[i]);
                    dp[0].insert(  *it  - stones[i]);
                    dp[0].insert(-(*it) - stones[i]);
                }
                dp[1].clear();
            }
        }

        vector<int> v;
        if( n % 2 ) {
            v.reserve(dp[0].size());
            for(auto it = dp[0].begin(); it != dp[0].end();)
                v.push_back(move(dp[0].extract(it++).value()));
        } else {
            v.reserve(dp[1].size());
            for(auto it = dp[1].begin(); it != dp[1].end();)
                v.push_back(move(dp[1].extract(it++).value()));
        }
        sort(v.begin(),v.end());
        return *lower_bound(v.begin(),v.end(),0);
    }
};
