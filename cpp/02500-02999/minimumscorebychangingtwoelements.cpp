
// 2567. Minimum Score by Changing Two Elements
// https://leetcode.com/problems/minimum-score-by-changing-two-elements/



/* example               [1,1,3,3,5,5,8,8]
 *   one possible change [1,1,3,3,5,5,5,5] => 4
 * example               [1,1,1,3,3,5,5,8,8,8]
 *   no change will minize the score further => 7
 *
 */
class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int n = nums.size();
        if( n == 3 )
            return 0;

        // by changing one value, we can always get rid
        // of the minimum low score, so we don't need to
        // worry about low score at all

        // we have the following options as we can make two changes
        //           0   1   ... n-2 n-1
        //           u   u       -   -
        //           u   -       -   d
        //           -   -       d   d

        sort(nums.begin(),nums.end());

        // initial high score
        int max_diff = nums[n-1] - nums[0];
        if( max_diff == 0 )
            return 0;

        int ans = INT_MAX;
        ans = min(ans, nums[n-1] - nums[2]);
        ans = min(ans, nums[n-2] - nums[1]);
        ans = min(ans, nums[n-3] - nums[0]);

        return ans;
    }
};
