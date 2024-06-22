
// 3105. Longest Strictly Increasing or Strictly Decreasing Subarray
// https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/





class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        int ans = 1;
        int l = 1;
        int mode = 1; // 0 increasing, 1 even, 2 decreasing
        for(int i = 1; i < n; ++i) {

            if( nums[i] == nums[i-1] ) {
                ans = max(ans, l);
                l = 1;
                mode = 1;

            } else if( nums[i] < nums[i-1] ) {
                if( mode == 0 ) {
                    ans = max(ans, l);
                    l = 2;
                    mode = 2;
                } else if( mode == 1 ) {
                    l = 2;
                    mode = 2;
                } else {
                    ++l;
                }

            } else { // nums[i] > nums[i-1]
                if( mode == 0 ) {
                    ++l;
                } else if( mode == 1 ) {
                    l = 2;
                    mode = 0;
                } else {
                    ans = max(ans, l);
                    l = 2;
                    mode = 0;
                }
            }
        }
        // finish up
        ans = max(ans, l);

        return ans;
    }
};
