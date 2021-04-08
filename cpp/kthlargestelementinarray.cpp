
// 215. Kth Largest Element in an Array
// https://leetcode.com/problems/kth-largest-element-in-an-array/


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(begin(nums),end(nums));
        return nums[nums.size()-k];
    }
};
