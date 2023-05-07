
// 2270. Number of Ways to Split Array
// https://leetcode.com/problems/number-of-ways-to-split-array/




class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();

        long prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        int cnt = 0;

        for(int i = 0; i < n-1; ++i)
            if( prefixSum[i+1] >= prefixSum[n] - prefixSum[i+1] )
                ++cnt;

        return cnt;
    }
};
