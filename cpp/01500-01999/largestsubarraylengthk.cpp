
// 1708. Largest Subarray Length K
// https://leetcode.com/problems/largest-subarray-length-k/


class Solution {
public:
    vector<int> largestSubarray(vector<int>& nums, int k) {
        size_t n = nums.size();
        if( k == n ) return nums;
        auto itb  = begin(nums);
        int j = distance(itb,max_element(itb,itb+(n-k+1)));

        vector<int> ans(k);
        for(int i = 0; i < k; ++i,++j)
            ans[i] = nums[j];
        return ans;
    }
};
