
// 2357. Make Array Zero by Subtracting Equal Amounts
// https://leetcode.com/problems/make-array-zero-by-subtracting-equal-amounts/


class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        // ans == nbr of distinct elements
        sort(begin(nums),end(nums));
        int prev = -1;
        int ans = 0;
        for(int x: nums)
            if( x != prev && x != 0 ) {
                ++ans;
                prev = x;
            }

        return ans;
    }
};
