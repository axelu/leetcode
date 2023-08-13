
// 2772. Apply Operations to Make All Array Elements Equal to Zero
// https://leetcode.com/problems/apply-operations-to-make-all-array-elements-equal-to-zero/




/* example
 *                  0 1 2 3 4 5 6
 * nums[i] original 2 2 4 2 4 2 2
 * nums[i] after    2 0 2 0 2 0 0
 * carry            2 2 2 2 2 2 0
 *
 */

class Solution {
public:
    bool checkArray(vector<int>& nums, int k) {
        if( k == 1 )
            return true;

        int n = nums.size();

        // sliding window
        int carry = 0;
        for(int i = 0; i < n; ++i) {
            if( carry > nums[i] ) // we would get negative
                return false;

            nums[i] = nums[i] - carry;
            carry = carry + nums[i]; // we need to remember that we still need to reduce nums[i]

            if( i >= k-1 )
                carry = carry - nums[i-k+1];
        }

        return carry == 0;
    }
};
