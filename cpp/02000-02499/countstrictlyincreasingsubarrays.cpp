
// 2393. Count Strictly Increasing Subarrays
// https://leetcode.com/problems/count-strictly-increasing-subarrays/




class Solution {
public:
    long long countSubarrays(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 10^5

        long long c[n+1];
        c[0] = 0;
        c[1] = 1;
        for(int i = 2; i <= n; ++i)
            c[i] = c[i-1] + i;

        long long ans = 0;
        int i = 0;
        int j = 1;
        for(; j < n; ++j) {

            if( nums[j] > nums[j-1] )
                continue;

            ans += j-1 > i ? c[j-i] : 1;
            i = j;
        }
        // finish up
        ans += j-1 > i ? c[j-i] : 1;

        return ans;
    }
};
