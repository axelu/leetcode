
// 3676. Count Bowl Subarrays
// https://leetcode.com/problems/count-bowl-subarrays/



class Solution {
private:
    long long solve(vector<int>& nums, int n) {
        long long ret = 0LL;
        stack<int> stck; // monotonically decreasing stack
        stck.push(nums[0]);
        for(int i = 1; i < n; ++i) {
            // note: nums[i-1] would also be the top element on our stack
            while( !stck.empty() && stck.top() < nums[i] )
                stck.pop();
            if( nums[i-1] < nums[i] && !stck.empty() )
                ++ret;
            stck.push(nums[i]);
        }

        return ret;
    }
public:
    long long bowlSubarrays(vector<int>& nums) {
        int n = nums.size(); // 3 <= nums.length <= 1e5; 1 <= nums[i] <= 1e9
        // nums consists of distinct elements

        // let us say we are at pos i with i > 1
        // if we look at element i-1 and nums[i-1] > nums[i], then
        // nums[i] is not the right end of any bowl, but
        // if nums[i-1] < nums[i], then we form a bowl with the first
        // element to our left where nums[0...i-2] > nums[i]
        // we can track those via a monotonically decreasing stack
        // then we we repeat going right to left

        /*
        long long ans = solve(nums, n);
        reverse(nums.begin(), nums.end());
        ans += solve(nums, n);
        return ans;
        */

        long long ret = 0LL;
        int mx_seen = nums[0];
        for(int i = 1; i < n; ++i) {
            if( nums[i-1] < nums[i] && mx_seen > nums[i] )
                ++ret;
            mx_seen = max(mx_seen, nums[i]);
        }
        reverse(nums.begin(), nums.end());
        mx_seen = nums[0];
        for(int i = 1; i < n; ++i) {
            if( nums[i-1] < nums[i] && mx_seen > nums[i] )
                ++ret;
            mx_seen = max(mx_seen, nums[i]);
        }
        return ret;
    }
};
