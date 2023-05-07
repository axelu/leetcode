
// 1558. Minimum Numbers of Function Calls to Make Target Array
// https://leetcode.com/problems/minimum-numbers-of-function-calls-to-make-target-array/




/*
 * func modify(arr, op, idx){
 *     //add by 1 index idx
 *     if (op == 0) {
 *         arr[idx] = add[idx] + 1
 *     }
 *     //multiply by 2 all elements
 *     if (op == 1) {
 *         for(i = 0; i < arr.length; i++) {
 *             arr[i] = arr[i] * 2
 *         }
 *     }
 *  }
 */

class Solution {
public:
    int minOperations(vector<int>& nums) {

        int op0 = 0; // add 1 to current element
        int op1 = 0; // multiply all elements by 2

        // division by 2 -> shift right, but only on even numbers

        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            int t = 0;
            while( x > 0 ) {
                if( x & 1 ) {
                    x &= ~1;
                    ++op0;
                } else {
                    x = x>>1;
                    ++t;
                }
            }
            op1 = max(op1,t);
        }

        return op0+op1;
    }
};
