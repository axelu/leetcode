
// 3467. Transform Array by Parity
// https://leetcode.com/problems/transform-array-by-parity/



class Solution {
public:
    vector<int> transformArray(vector<int>& nums) {
        for(int& x: nums)
            x = x % 2;
        sort(begin(nums),end(nums));

        return nums;
    }
};
