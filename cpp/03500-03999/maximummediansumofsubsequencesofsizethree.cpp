
// 3627. Maximum Median Sum of Subsequences of Size 3
// https://leetcode.com/problems/maximum-median-sum-of-subsequences-of-size-3/


class Solution {
public:
    long long maximumMedianSum(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());

        int n = nums.size();
        long long ans = 0LL;
        for(int i = 1; i < 2*n/3; i += 2)
            ans += (long long)nums[i];

        return ans;
    }
};
