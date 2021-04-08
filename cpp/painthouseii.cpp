
// 265. Paint House II
// https://leetcode.com/problems/paint-house-ii/


// solution approach #2
class Solution {
public:
    int minCostII(vector<vector<int>> costs) {
        size_t n = costs.size();
        if( 0 == n ) return 0;
        size_t k = costs[0].size();

        for(int i = 1; i < n; ++i) {     // house
            for(int j = 0; j < k; ++j) { // color
                int mn = INT_MAX;
                for(int prev = 0; prev < k; ++prev) {
                    if( j == prev) continue;
                    mn = min(mn, costs[i-1][prev]);
                }
                costs[i][j] += mn;
            }
        }

        // get the minimum in last row
        int mn = INT_MAX;
        for(int c : costs[n-1])
            mn = min(mn,c);
        return mn;
    }
};
