
// 2104. Sum of Subarray Ranges
// https://leetcode.com/problems/sum-of-subarray-ranges/




class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 1000

        long long ans = 0LL;

        /*
        // brute force
        for(int i = 0; i < n-1; ++i) {
            int mn = nums[i];
            int mx = nums[i];
            for(int j = i+1; j < n; ++j) {
                mn = min(mn,nums[j]);
                mx = max(mx,nums[j]);
                ans += mx - mn;
            }
        }
        */

        // based on solution approach
        stack<int> inc; // monotonic increasing stack, idx of element
		stack<int> dec; // monotonic decreasing stack, idx of element
		for(int i = 0; i < n; ++i) {

			while( !inc.empty() && nums[inc.top()] >= nums[i] ) {
				int mid = inc.top();
				inc.pop();

                int right = i;
				int left = inc.empty() ? -1: inc.top();

                // number of subarrays where nums[mid] is the minimum
                long long minTime = (mid - left) * (right - mid);
				ans = ans - nums[mid] * minTime;
			}
			inc.push(i);

			while( !dec.empty() && nums[dec.top()] <= nums[i] ) {
				int mid = dec.top();
				dec.pop();

				int right = i;
				int left = dec.empty() ? -1: dec.top();

                // number of subarrays where nums[mid] is the maximum
				long long maxTime = (mid - left) * (right - mid);
				ans = ans + nums[mid] * maxTime;
			}
			dec.push(i);
		}
        // finish up
        while( !inc.empty() ) {
            int mid = inc.top();
            inc.pop();

            int right = n;
            int left = inc.empty() ? -1: inc.top();

            long long minTime = (mid - left) * (right - mid);
            ans = ans - nums[mid] * minTime;
        }
        while( !dec.empty() ) {
            int mid = dec.top();
            dec.pop();

            int right = n;
            int left = dec.empty() ? -1: dec.top();

            long long maxTime = (mid - left) * (right - mid);
            ans = ans + nums[mid] * maxTime;
        }

        return ans;
    }
};
