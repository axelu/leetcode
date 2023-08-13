
// 163. Missing Ranges
// https://leetcode.com/problems/missing-ranges/

class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        size_t n = nums.size();

        vector<vector<int>> ans;
        
        // base case
        if( 0 == n ) {
            ans.push_back({lower,upper});
            return ans;
        }        
        
        // gap in the beginning?
        if( lower < nums[0] ) {
            ans.push_back({lower,nums[0]-1});
        }        
        
        for(int i = 0; i < n-1; ++i) {
            if(nums[i]+1 != nums[i+1] ) {
                ans.push_back({nums[i]+1,nums[i+1]-1});
            }
        }
        
        // gap at the end?
        if( upper > nums[n-1] ) {
            ans.push_back({nums[n-1]+1,upper});    
        }

        return ans;
    }
};
