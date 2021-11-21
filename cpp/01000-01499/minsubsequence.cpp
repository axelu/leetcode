
// 1403. Minimum Subsequence in Non-Increasing Order
// https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/


class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        auto n = nums.size();
        if( n == 1 ) return nums;

        sort(begin(nums),end(nums));
        int m = accumulate(begin(nums),end(nums),0);

        vector<int> r = {};
        int sum = 0; // subsequence sum
        for(int i = n-1; i >= 0; --i) {
            r.push_back(nums[i]);
            sum += nums[i];
            if( sum > m - sum ) break;
        }

        return r;
    }
};
