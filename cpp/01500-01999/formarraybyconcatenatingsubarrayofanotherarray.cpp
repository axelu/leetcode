
// 1764. Form Array by Concatenating Subarrays of Another Array
// https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/




class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int grp_sz = groups.size();
        int n = nums.size();

        int g = 0;  // group index
        int j = 0;  // index in current group
        int f = -1; // remember last position in nums that match current groups 1st char
        for(int i = 0; i < n; ++i) {
            if( j > 0 && f == -1 ) {
                if( groups[g][0] == nums[i] )
                    f = i;
            }

            if( groups[g][j] == nums[i] ) {
                ++j;
                if( j == groups[g].size() ) {
                    ++g;
                    if( g == grp_sz ) {
                        return true;
                    }
                    j = 0;
                    f = -1;
                }

            } else {
                // reset index in current group
                j = 0;
                // we also need to go back in nums to the 1st index
                // that does not overlap (aka is disjoint) from prior match
                // where groups[g][0] == nums[i]
                if( f != -1 ) {
                    i = f - 1; // -1 as the loop will advance i;
                    f = -1;
                }
            }
        }

        return false;
    }
};
