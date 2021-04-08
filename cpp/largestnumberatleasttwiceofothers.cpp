
// 747. Largest Number At Least Twice of Others
// https://leetcode.com/problems/largest-number-at-least-twice-of-others/



class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int n = nums.size();
        int mx = 0;      // nums[i] will be an integer in the range [0, 99]
        int mxIdx = -1;

        // pass 1
        for(int i = 0; i < n; ++i)
            if( nums[i] > mx ) {
                mx = nums[i];
                mxIdx = i;
            }
        // pass 2
        for(int i = 0; i < n; ++i)
            if( nums[i] != mx && nums[i]*2 > mx ) return -1;

        return mxIdx;
    }
};
