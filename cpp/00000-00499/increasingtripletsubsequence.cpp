
// 334. Increasing Triplet Subsequence
// https://leetcode.com/problems/increasing-triplet-subsequence/

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        
        if( n < 3 ) 
            return false;
        if( n == 3 ) 
            return nums[0] < nums[1] && nums[1] < nums[2];
        
        
        long mn  = LONG_MAX;
        long mn2 = LONG_MAX;
        

        for(int i = 0; i < n; ++i) {

            if( nums[i] <= mn )
                mn = nums[i];
            else if( nums[i] <= mn2 )
                mn2 = nums[i];
            else
                return true;
        }
        
        return false;        
   }
};
