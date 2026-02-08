
// 3828. Final Element After Subarray Deletions
// https://leetcode.com/problems/final-element-after-subarray-deletions/


class Solution {
public:
    int finalElement(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];

        return nums[0] > nums[n-1] ? nums[0] : nums[n-1];
    }
};
