
// 1909. Remove One Element to Make the Array Strictly Increasing
// https://leetcode.com/problems/remove-one-element-to-make-the-array-strictly-increasing/




class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        int n = nums.size();

        /*
         * example 125389 true, delete either the 5 or the 3
         * example 127189 true, delete the 1 in the middle
         * example 127345 true, delete the 7
         * example 127145 false
         */

        int removed = false;
        for(int i = 1; i < n; ++i) {

            if( nums[i-1] >= nums[i] ) {
                if( removed )
                    return false;

                // can we remove nums[i] or nums[i-1] to make it strictly increasing?
                if( i == n-1 || nums[i-1] < nums[i+1] ) {
                    ++i;
                    removed = true;
                } else if( i == 1 || nums[i-2] < nums[i] ) {
                    removed = true;
                } else {
                    return false;
                }
            }
        }


        return true;
    }
};
