
// 2733. Neither Minimum nor Maximum
// https://leetcode.com/problems/neither-minimum-nor-maximum/



class Solution {
public:
    int findNonMinOrMax(vector<int>& nums) {
        const auto [mn, mx] = minmax_element(nums.begin(),nums.end());
        int ans = -1;
        for(int x: nums)
            if( x != *mn && x != *mx ) {
                ans = x;
                break;
            }
        return ans;
    }
};
