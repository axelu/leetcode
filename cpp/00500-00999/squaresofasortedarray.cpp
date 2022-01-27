
// 977. Squares of a sorted Array
// https://leetcode.com/problems/squares-of-a-sorted-array/
// day 15 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/571/week-3-december-15th-december-21st/3567/


class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        size_t n = nums.size();
        vector<int> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = nums[i] * nums[i];
        sort(ans.begin(),ans.end());
        return ans;
    }
};
