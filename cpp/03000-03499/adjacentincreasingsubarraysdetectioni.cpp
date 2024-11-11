
// 3349. Adjacent Increasing Subarrays Detection I
// https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/





class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        for(int i = 0; i <= n-(2*k); ++i) {

            bool lft_is_increasing = true;
            for(int o = i+1; o < i+k; ++o) {
                if( nums[o-1] >= nums[o] ) {
                    lft_is_increasing = false;
                    break;
                }
            }
            if( lft_is_increasing ) {
                bool rgt_is_increasing = true;
                int o = i + k+1;
                for(; o < i + (2*k); ++o) {
                    if( nums[o-1] >= nums[o] ) {
                        rgt_is_increasing = false;
                        break;
                    }
                }
                if( rgt_is_increasing )
                    return true;
                else
                    i = o - k - 1; // loop advances i
            }
        }

        return false;
    }
};
