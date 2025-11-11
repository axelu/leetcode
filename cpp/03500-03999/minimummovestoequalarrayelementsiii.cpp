
// 3736. Minimum Moves to Equal Array Elements III
// https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/


class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 100

        int mx = INT_MIN;
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += nums[i];
            mx = max(mx, nums[i]);
        }

        return n * mx - sum;
    }
};
