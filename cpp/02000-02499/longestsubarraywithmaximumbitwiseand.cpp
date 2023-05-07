
// 2419. Longest Subarray With Maximum Bitwise AND
// https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/



class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();

        // from the problem description
        //    let k be the maximum value of the bitwise AND of any subarray of nums
        // => with that k is the max value nums[i] with 0 <= i <= n
        // with that the question becomes: max consecutive k's

        int ans = 1;
        int mx = nums[0];

        int t = 1;
        for(int i = 1; i < n; ++i) {

            if( nums[i] > mx ) {
                mx = nums[i];
                ans = 1;
                t = 1;

            } else if( nums[i] == mx ) {
                if( nums[i] == nums[i-1] ) {
                    ++t;
                    ans = max(ans,t);
                } else {
                    t = 1;
                }
            }
        }

        return ans;
    }
};
