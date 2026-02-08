
// 3774. Absolute Difference Between Maximum and Minimum K Elements
// https://leetcode.com/problems/absolute-difference-between-maximum-and-minimum-k-elements/


class Solution {
public:
    int absDifference(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 || k == n )
            return 0;

        sort(nums.begin(), nums.end());

        int mn_sum = 0;
        for(int i = 0; i < k; ++i)
            mn_sum += nums[i];

        int mx_sum = 0;
        for(int i = n-1; i >= n-k; --i)
            mx_sum += nums[i];

        return abs(mx_sum - mn_sum);
    }
};
