
// 2428. Maximum Sum of an Hourglass
// https://leetcode.com/problems/maximum-sum-of-an-hourglass/



class Solution {
public:
    int maxSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> prefixSum(m,vector<int>(n+1,0));
        for(int i = 0; i < m; ++i)
            for(int j = 1; j <= n; ++j)
                prefixSum[i][j] = prefixSum[i][j-1] + grid[i][j-1];

        int ans = 0;

        for(int i = 0; i <= m-3; ++i)
            for(int j = 0; j <= n-3; ++j) {

                int t = prefixSum[i][j+3] - prefixSum[i][j];
                t += grid[i+1][j+1];
                t += prefixSum[i+2][j+3] - prefixSum[i+2][j];

                ans = max(ans,t);
            }

        return ans;
    }
};
