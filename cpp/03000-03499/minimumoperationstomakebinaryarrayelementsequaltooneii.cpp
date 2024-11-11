
// 3192. Minimum Operations to Make Binary Array Elements Equal to One II
// https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-ii/




class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        int ans = 0; // number of flips

        for(int i = 0; i < n; ++i) {
            // if ans % 2 == 0 then nums[i] is in original state
            // if ans % 2 == 1 then nums[i] is opposite to original state

            if( (ans % 2 == 0 && nums[i] == 0) || (ans % 2 == 1 && nums[i] == 1) )
                ++ans;
        }

        return ans;
    }
};
