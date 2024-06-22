
// 2980. Check if Bitwise OR Has Trailing Zeros
// https://leetcode.com/problems/check-if-bitwise-or-has-trailing-zeros/



class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        int cnt_divisible_by_two = 0;

        for(int x: nums)
            if( !(x & 1) ) {
                ++cnt_divisible_by_two;
                if( cnt_divisible_by_two == 2 )
                    break;
            }

        return cnt_divisible_by_two == 2;
    }
};
