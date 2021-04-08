
// 674. Longest Continuous Increasing Subsequence
// https://leetcode.com/problems/longest-continuous-increasing-subsequence/



class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        if( n == 0 ) return 0;
        if( n == 1 ) return 1;

        int ans = 1;
        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if( nums[i] > nums[i-1] ) {
                ++cnt;
                if( i == n-1 && cnt > ans ) ans = cnt;
            } else {
                if( cnt > ans ) ans = cnt;
                cnt = 1;
            }
        }
        return ans;
    }
};
