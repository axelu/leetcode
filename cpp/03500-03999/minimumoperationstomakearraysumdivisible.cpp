
// 3512. Minimum Operations to Make Array Sum Divisible by K
// https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/



class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int sum = accumulate(begin(nums), end(nums), 0);
        return sum % k;
    }
};
