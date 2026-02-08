
// 3745. Maximize Expression of Three Elements
// https://leetcode.com/problems/maximize-expression-of-three-elements/description/


class Solution {
public:
    int maximizeExpressionOfThree(vector<int>& nums) {
        int n = nums.size(); // 3 <= n <= 100

        sort(begin(nums), end(nums));
        // 0 1 2 ... n-2 n-1
        // c          b   a

        return nums[n-1] + nums[n-2] - nums[0];
    }
};
