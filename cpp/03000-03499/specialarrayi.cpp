
// 3151. Special Array I
// https://leetcode.com/problems/special-array-i/




class Solution {
public:
    bool isArraySpecial(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return true;

        for(int i = 1; i < n; ++i)
            if( nums[i-1] % 2  == nums[i] % 2 )
                return false;


        return true;
    }
};
