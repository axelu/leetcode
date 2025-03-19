
// 3462. Maximum Sum With at Most K Elements
// https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/



class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();    // rows

        for(int i = 0; i < n; ++i)
            sort(begin(grid[i]), end(grid[i]), greater<int>());

        vector<pair<int,int>> v; // value, row
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < limits[i]; ++j)
                v.push_back({grid[i][j], i});
        }

        sort(begin(v), end(v), [](const pair<int,int>& a, const pair<int,int>& b){
            return a.first > b.first;
        });

        long long ans = 0LL;

        for(int i = 0; i < v.size() && k > 0; ++i) {
            int r = v[i].second;
            if( limits[r] > 0 ) {
                ans += (long long)v[i].first;
                --limits[r];
                --k;
            }
        }

        return ans;
    }
};
