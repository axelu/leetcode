
// 2640. Find the Score of All Prefixes of an Array
// https://leetcode.com/problems/find-the-score-of-all-prefixes-of-an-array/




class Solution {
public:
    vector<long long> findPrefixScore(vector<int>& nums) {
        int n = nums.size();

        vector<long long> ans(n);

        ans[0] = nums[0] + nums[0];
        int mx = nums[0];
        long long sum = ans[0];
        for(int i = 1; i < n; ++i) {
            mx = max(mx, nums[i]);
            sum = nums[i] + mx;
            ans[i] = ans[i-1] + sum;
        }

        return ans;
    }
};
