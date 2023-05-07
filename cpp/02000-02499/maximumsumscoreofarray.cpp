
// 2219. Maximum Sum Score of Array
// https://leetcode.com/problems/maximum-sum-score-of-array/





class Solution {
public:
    long long maximumSumScore(vector<int>& nums) {
        int n = nums.size();

        long prefixSum[n+1]; // based on the constraints, long sufficient
        prefixSum[0] = 0L;

        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        long mx = LONG_MIN;

        for(int i = 0; i < n; ++i) {
            // sum of the first i + 1 elements
            long f = prefixSum[i+1];

            // sum of the last n - i elements
            long l = prefixSum[n] - prefixSum[i];

            mx = max({mx,f,l});
        }

        return mx;
    }
};
