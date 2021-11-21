
// 78. SUbsets
// https://leetcode.com/problems/subsets/




class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> ans;
        vector<int> t;

        int j;
        for(int i = 0; i < pow(2,n); ++i) {
            t.clear();
            for(j = 0; j < n; ++j) {
                if( i & (1<<j) ) t.push_back(nums[j]);
            }
            ans.push_back(t);
        }

        return ans;
    }
};
