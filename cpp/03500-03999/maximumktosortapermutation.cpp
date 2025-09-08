
// 3644. Maximum K to Sort a Permutation
// https://leetcode.com/problems/maximum-k-to-sort-a-permutation/



class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        // observation using perms of 0,1,2,3,4,5,6,7
        // do an AND of all the positions that are not in the right place

        int _and = -1;
        for(int i = 0; i < nums.size(); ++i) {
            if( nums[i] != i ) {
                if( _and == -1 )
                    _and = nums[i];
                else
                    _and = _and & nums[i];
            }
        }

        return _and == -1 ? 0 : _and;
    }
};
