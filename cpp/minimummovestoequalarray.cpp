
// 453. Minimum Moves to Equal Array Elements
// https://leetcode.com/problems/minimum-moves-to-equal-array-elements/



class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return 0;
        sort(nums.begin(),nums.end());
        int ans = 0;
        for(int i = n-1; i > 0; i--) {
            ans += nums[i] - nums[0];
        }
        return ans;
    }
};
