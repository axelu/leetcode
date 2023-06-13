
// 2679. Sum in a Matrix
// https://leetcode.com/problems/sum-in-a-matrix/




class Solution {
public:
    int matrixSum(vector<vector<int>>& nums) {
        int m = nums.size();    // rows
        int n = nums[0].size(); // cols


        priority_queue<int> pqs[m];
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                pqs[i].push(nums[i][j]);
            }
        }

        int ans = 0;

        for(int j = 0; j < n; ++j) {
            int mx = 0;
            for(int i = 0; i < m; ++i) {
                mx = max(mx,pqs[i].top());
                pqs[i].pop();
            }
            ans += mx;
        }

        return ans;
    }
};
