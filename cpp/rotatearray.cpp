
// Rotate Array
// https://leetcode.com/problems/rotate-array/


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if ( nums.empty() ) return;
        if ( nums.size() == 1 ) return;
        if ( k == 0 || k == nums.size() ) return;
        if ( k > nums.size() ) k = k % nums.size();
        if ( k == 0 ) return;

        ::rotate(nums.begin(), nums.end() - k, nums.end());
    }
};
