
// 3427. Sum of Variable Length Subarrays
// https://leetcode.com/problems/sum-of-variable-length-subarrays/




class Solution {
private:
    int prefixSum[101];
public:
    int subarraySum(vector<int>& nums) {
        int n = nums.size();

        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        int ans = 0;

        for(int i = 0; i < n; ++i) {
            int start = max(0, i - nums[i]);
            ans += prefixSum[i+1] - prefixSum[start];
        }

        return ans;
    }
};
