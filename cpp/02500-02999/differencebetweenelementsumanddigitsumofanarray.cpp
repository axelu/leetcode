
// 2535. Difference Between Element Sum and Digit Sum of an Array
// https://leetcode.com/problems/difference-between-element-sum-and-digit-sum-of-an-array/




class Solution {
public:
    int differenceOfSum(vector<int>& nums) {
        int element_sum = 0;
        int digit_sum = 0;

        for(int x: nums) {
            element_sum += x;

            while( x > 0 ) {
                digit_sum += x % 10;
                x /= 10;
            }
        }

        return abs(element_sum - digit_sum);
    }
};
