
// 2760. Longest Even Odd Subarray With Threshold
// https://leetcode.com/problems/longest-even-odd-subarray-with-threshold/




class Solution {
public:
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int n = nums.size();

        int ans = 0;

        for(int i = 0; i < n; ++i) {
            if( nums[i] % 2 == 0 && nums[i] <= threshold ) {
                // we have a starting point
                // expand our window as far as we can
                int j = i;
                int alternate = 1;
                while( j+1 < n && nums[j+1] % 2 == alternate and nums[j+1] <= threshold ) {
                    ++j;
                    alternate = !alternate;
                }

                ans = max(ans, j - i + 1);
                i = j;
            }
        }


        return ans;
    }
};
