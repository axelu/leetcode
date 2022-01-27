
// 1685. Sum of Absolute Differences in a Sorted Array
// https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/


class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        // nums is sorted in non-decreasing order
        // everything left of i is less or equal nums[i]
        // everything right of i is greater or equal nums[i]
        // hence
        // ans[i] = (nums[i]-nums[0]) + ... + (nums[i]-nums[i-1]) + <- left of i
        //          (nums[i+1]-nums[i]) + ... (nums[n-1]-nums[i])   <- right of i

        // left:  i*nums[i] - sum[0,i-1]
        // right: sum[i+1,n-1] - (n-1-i)*nums[i]

        int n = nums.size();
        int prefixSum[n+1];prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + nums[i];

        vector<int> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = (i*nums[i] - prefixSum[i]) + ((prefixSum[n]-prefixSum[i+1]) - (n-1-i)*nums[i]);

        return ans;
    }
};
