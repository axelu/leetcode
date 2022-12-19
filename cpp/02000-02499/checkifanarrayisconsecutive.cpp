
// 2229. Check if an Array Is Consecutive
// https://leetcode.com/problems/check-if-an-array-is-consecutive/



class Solution {
public:
    bool isConsecutive(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return true;

        sort(begin(nums),end(nums));
        for(int i = 1; i < n; ++i)
            if( nums[i-1] != nums[i]-1 )
                return false;

        return true;
    }
};
