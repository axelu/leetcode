
// 1567. Maximum Length of Subarray With Positive Product
// https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/



class Solution {
private:
    int getMaxLen(vector<int>& nums, int n) {
        int ans = 0;
        
        int flip_run = 0;
        int flip_run_sign; // 0 negative, 1 positive
        int positive_run = 0;
        int negative_run = 0;
        int negative_run_sign; // 0 negative, 1 positive
        int seenFirstNegative = false;
        
        for(int i = 0; i < n; ++i) {
            if( nums[i] > 0 ) {
                if( flip_run == 0 )
                    flip_run_sign = 1;
                ++flip_run;
                ++positive_run; 
                if( seenFirstNegative ) {
                    if( negative_run == 0 )
                        negative_run_sign = 1;
                    ++negative_run;
                }
            } else if( nums[i] < 0 ) {
                flip_run_sign = flip_run == 0 ? 0 : !flip_run_sign;
                ++flip_run;
                ans = max(ans,positive_run);
                positive_run = 0;
                if( seenFirstNegative ) {
                    negative_run_sign = negative_run == 0 ? 0 : !negative_run_sign;
                    ++negative_run;
                }
                seenFirstNegative = true;
            } else { // nums[i] == 0
                flip_run = 0;
                ans = max(ans,positive_run);
                positive_run = 0;
                negative_run = 0;
                seenFirstNegative = false;
            }
            if( flip_run_sign )
                ans = max(ans,flip_run);
            if( negative_run_sign )
                ans = max(ans,negative_run);
        }
        // finish up
        ans = max(ans,positive_run);
        
        return ans;
    }

public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        return getMaxLen(nums,n);
    }
};
