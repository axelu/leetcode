
// 1413. Minimum Value to Get Positive Step by Step Sum
// https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/



class Solution {
public:
    int minStartValue(vector<int>& nums) {
        auto n = nums.size();
        if( n == 1 )
            return nums[0] > -1 ? 1 : abs(nums[0]-1);

        int prefixSum[100];
        prefixSum[0] = nums[0];
        int minPrefixSum = nums[0];
        for (int i = 1; i < n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
            minPrefixSum = min(minPrefixSum,prefixSum[i]);
        }

        return minPrefixSum > -1 ? 1 : abs(minPrefixSum-1);
    }
};
