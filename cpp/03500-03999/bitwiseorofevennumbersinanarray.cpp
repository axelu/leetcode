
// 3688. Bitwise OR of Even Numbers in an Array
// https://leetcode.com/problems/bitwise-or-of-even-numbers-in-an-array/



class Solution {
public:
    int evenNumberBitwiseORs(vector<int>& nums) {
        int _or = 0;
        for(int x: nums)
            if( x % 2 == 0 )
                _or |= x;
        return _or;
    }
};
