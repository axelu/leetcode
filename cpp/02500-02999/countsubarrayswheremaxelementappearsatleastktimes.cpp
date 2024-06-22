
// 2962. Count Subarrays Where Max Element Appears at Least K Times
// https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/





class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        int mx = *max_element(nums.begin(),nums.end());

        // find the initial window that has max k times
        int l = -1; int r = -1;
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            if( nums[i] == mx ) {
                if( l == -1 )
                    l = i;
                ++cnt;
                if( cnt == k ) {
                    r = i;
                    break;
                }
            }
        }

        if( r == -1 )
            return 0LL;

        long long ans = (long long)(l + 1) * (n - r);

        while( true ) {

            int prev_l = l;
            // advance l to the next mx
            ++l;
            while( l < n && nums[l] != mx )
                ++l;
            if( l == n )
                break;

            // advance r to the next mx
            ++r;
            while( r < n && nums[r] != mx )
                ++r;
            if( r == n )
                break;

            ans += (long long)(l - prev_l) * (n - r);
        }


        return ans;
    }
};
