
// 2202. Maximize the Topmost Element After K Moves
// https://leetcode.com/problems/maximize-the-topmost-element-after-k-moves/





class Solution {
public:
    int maximumTop(vector<int>& nums, int k) {
        int n = nums.size();

        // edge cases
        if( k == 0 )
            return nums[0];
        if( n == 1 )
            return k % 2 == 0 ? nums[0] : -1;
        if( k == 1 )
            return nums[1];

        if( k < n ) {
            auto itb = nums.begin();
            auto ite = nums.begin();advance(ite,k-1);
            int mx = *max_element(itb,ite);
            return max(nums[k],mx);

        } else if( k == n ) {
            auto itb = nums.begin();
            auto ite = nums.begin();advance(ite,k-1);
            int mx = *max_element(itb,ite);
            return mx;

        } else {
            return *max_element(nums.begin(),nums.end());
        }
    }
};
