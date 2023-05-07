
// 2574. Left and Right Sum Differences
// https://leetcode.com/problems/left-and-right-sum-differences/



class Solution {
public:
    vector<int> leftRigthDifference(vector<int>& nums) {
        int n = nums.size();

        // left Sum == prefixSum
        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        // rightSum = suffixSum
        int suffixSum[n+1];
        suffixSum[n] = 0;
        for(int i = n-1; i >= 0; --i)
            suffixSum[i] = suffixSum[i+1] + nums[i];

        vector<int> ans(n);

        for(int i = 0; i < n; ++i)
            ans[i] = abs(prefixSum[i] - suffixSum[i+1]);

        return ans;
    }
};
