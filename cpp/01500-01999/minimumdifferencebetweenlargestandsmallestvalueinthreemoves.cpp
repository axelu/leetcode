
// 1509. Minimum Difference Between Largest and Smallest Value in Three Moves
// https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/


class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if( n <= 3 )
            return 0;

        sort(nums.begin(),nums.end());

        int mn_diff = nums[n-1] - nums[0];

        for(int i = 0; i < 4; ++i) {
            // remove i elements from front
            int mn = nums[0+i];

            // remove 3-i elements from end
            int mx = nums[n-1-(3-i)];

            int diff = mx - mn;
            mn_diff = min(mn_diff,diff);
        }

        return mn_diff;
    }
}
