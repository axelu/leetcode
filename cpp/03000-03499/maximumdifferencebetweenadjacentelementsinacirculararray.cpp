
// 3423. Maximum Difference Between Adjacent Elements in a Circular Array
// https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/




class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size();

        int ans = 0;
        int pre = nums[n-1];
        for(int i = 0; i < n; ++i) {
            ans = max(ans, abs(nums[i] - pre));
            pre = nums[i];
        }

        return ans;
    }
};
