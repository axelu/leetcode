
// 1827. Minimum Operations to Make the Array Increasing
// https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/




class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return 0;
        int ans = 0,t;
        for(int i = 1; i < n; ++i) {
            t = nums[i];
            nums[i] = max(nums[i-1]+1,nums[i]);
            ans += nums[i]-t;
        }
        return ans;
    }
};
