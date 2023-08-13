
// 2740. Find the Value of the Partition
// https://leetcode.com/problems/find-the-value-of-the-partition/



class Solution {
public:
    int findValueOfPartition(vector<int>& nums) {
        int n = nums.size();

        sort(nums.begin(),nums.end());

        int ans = INT_MAX;

        for(int i = 1; i < n; ++i)
            ans = min(ans, nums[i] - nums[i-1]);

        return ans;
    }
};
