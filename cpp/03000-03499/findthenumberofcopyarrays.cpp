
// 3468. Find the Number of Copy Arrays
// https://leetcode.com/problems/find-the-number-of-copy-arrays/





class Solution {
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        int n = original.size(); // bounds.size() == n

        int ans = INT_MAX;

        vector<vector<int>> act_bounds(n,vector<int>(2));
        act_bounds[0] = bounds[0];
        for(int i = 1; i < n; ++i) {
            int d = original[i] - original[i-1];

            int copy_upper_bound = bounds[i][1];
            int copy_lower_bound = bounds[i][0];

            if( copy_lower_bound > act_bounds[i-1][1] + d )
                return 0;
            if( copy_upper_bound < act_bounds[i-1][0] + d )
                return 0;

            act_bounds[i][1] = min(act_bounds[i-1][1] + d, bounds[i][1]);
            act_bounds[i][0] = max(act_bounds[i-1][0] + d, bounds[i][0]);

            ans = min(ans, act_bounds[i][1] - act_bounds[i][0]);
        }

        return ans + 1;
    }
};
