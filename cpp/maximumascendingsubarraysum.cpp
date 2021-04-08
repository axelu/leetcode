
// 1800. Maximum Ascending Subarray Sum
// https://leetcode.com/problems/maximum-ascending-subarray-sum/


class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int n = nums.size();
        int ans = nums[0];
        int s = nums[0];
        for(int i = 1; i < n; ++i) {
            if( nums[i] <= nums[i-1] ) {
                ans = max(ans,s);
                s = 0;
            }
            s += nums[i];
        }
        ans = max(ans,s);

        return ans;
    }
};
