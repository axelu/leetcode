
// 283. Move Zeroes
// https://leetcode.com/problems/move-zeroes/



class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        size_t n = nums.size();
        if( n <= 1 ) return;

        int i = 0;
        for(int j = 1; j < n; ++j) {
            if( nums[j] != 0 ) {
                // advance i to a 0 and swap
                while( i < j ) {
                    if( nums[i] == 0 ) break;
                    ++i;
                }
                if( i != j ) {
                    nums[i] = nums[j];
                    nums[j] = 0;
                }
            }
        }
    }
};
