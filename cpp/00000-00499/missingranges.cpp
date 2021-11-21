
// 163. Missing Ranges
// https://leetcode.com/problems/missing-ranges/


class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        size_t n = nums.size();
        vector<string> ans;
        string s;

        // base case
        if( 0 == n ) {
            s = to_string(lower);
            if( lower != upper )
                s += "->" + to_string(upper);
            ans.push_back(s);
            return ans;
        }

        // gap in the beginning?
        if( lower < nums[0] ) {
            s = to_string(lower);
            if( lower < nums[0]-1 )
                s += "->" + to_string(nums[0]-1);
            ans.push_back(s);
        }

        for(int i = 0; i < n-1; ++i) {
            if(nums[i]+1 != nums[i+1] ) {
                s = to_string(nums[i]+1);
                if( nums[i+1] != nums[i]+2 )
                    s += "->" + to_string(nums[i+1]-1);
                ans.push_back(s);
            }
        }

        // gap at the end?
        if( upper > nums[n-1] ) {
            s = to_string(upper);
            if( upper > nums[n-1]+1 )
                s = to_string(nums[n-1]+1) + "->" + s;
            ans.push_back(s);
        }

        return ans;
    }
};
