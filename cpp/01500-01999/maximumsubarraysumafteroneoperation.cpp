
// 1746. Maximum Subarray Sum After One Operation
// https://leetcode.com/problems/maximum-subarray-sum-after-one-operation/


class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0]*nums[0];

        // left to right
        int prefixSum[n+1]; // max ending at i
        prefixSum[0] = 0;
        int t;
        for(int i = 0; i < n; ++i) {
            t = prefixSum[i] + nums[i];
            prefixSum[i+1] = t < 0 ? 0 : t;
        }
        // right to left
        int suffixSum[n+1]; // max starting at i
        suffixSum[n] = 0;
        for(int i = n-1; i >= 0; --i) {
            t = suffixSum[i+1] + nums[i];
            suffixSum[i] = t < 0 ? 0 : t;
        }

        int ans = INT_MIN;
        for(int i = 0; i < n; ++i) {
            t = prefixSum[i] + nums[i]*nums[i] + suffixSum[i+1];
            ans = max(ans,t);
        }

        return ans;
    }
};
