
// 3708. Longest Fibonacci Subarray
// https://leetcode.com/problems/longest-fibonacci-subarray/



class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();

        int ans = 2;

        int i = 0;
        for(int j = 1; j < n-1; ++j) {
            long long val_pre = (long long)nums[j-1];
            long long val_cur = (long long)nums[j];
            long long val_nxt = (long long)nums[j+1];

            if( val_pre + val_cur == val_nxt) {
                ans = max(ans, (j+1) - i + 1);
            } else {
                i = j;
            }
        }

        return ans;
    }
};
