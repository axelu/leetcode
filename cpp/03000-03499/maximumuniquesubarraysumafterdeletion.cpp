
// 3487. Maximum Unique Subarray Sum After Deletion
// https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/




class Solution {
public:
    int maxSum(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 100; -100 <= nums[i] <= 100

        set<int> uniques;
        for(int x: nums)
            uniques.insert(x);

        // if there are no positive integers in nums, then the
        // largest integer we have is the ans, as we cannot be non-empty
        if( *uniques.rbegin() <= 0 )
            return *uniques.rbegin();

        // otherwise we sum all unique positive integers as the answer
        int ans = 0;
        for(auto it = uniques.rbegin(); it != uniques.rend() && *it > 0; ++it)
            ans += *it;

        return ans;
    }
};
