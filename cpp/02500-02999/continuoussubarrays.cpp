
// 2762. Continuous Subarrays
// https://leetcode.com/problems/continuous-subarrays/




/* formula of number of non-empty subarrays for array of length k
 * for all subarrays of length [1,k] inclusive: n * ((n+1)/2)
 */
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        long long ans = 0LL;

        // monotonic increasing 'stack'
        // at each step, remove anything equal or greater from back
        // front holds min
        deque<array<long long,2>> mn; // val,index
        mn.push_back({nums[0],0});

        // monotonic decreasing stack
        // at each step, remove anything equal or smaller from back
        deque<array<long long,2>> mx; // val, index
        mx.push_back({nums[0],0});

        long long i = 0; // start of our continuous subarray
        for(long long j = 1; j < n; ++j) {
            // if the current value in nums compared with
            // min or max in our stacks exceeds the threshold,
            // then we need to tally up.

            if( nums[j] > mn.front()[0] && nums[j] - mn.front()[0] > 2 ) {
                long long t1 = (j-i) * (j-i+1)/2;
                while( !mn.empty() && nums[j] - mn.front()[0] > 2 ) {
                    i = mn.front()[1]+1;
                    mn.pop_front();
                }
                long long t2 = (j-i) * (j-i+1)/2;
                long long t = t1 - t2;
                ans = ans + t;

            } else if( nums[j] < mx.front()[0] && mx.front()[0] - nums[j] > 2 ) {
                long long t1 = (j-i) * (j-i+1)/2;
                while( !mx.empty() && mx.front()[0] - nums[j] > 2 ) {
                    i = mx.front()[1]+1;
                    mx.pop_front();
                }
                long long t2 = (j-i) * (j-i+1)/2;
                long long t = t1 - t2;
                ans = ans + t;
            }

            while( !mn.empty() && mn.back()[0] >= nums[j] )
                mn.pop_back();
            mn.push_back({nums[j],j});

            while( !mx.empty() && mx.back()[0] <= nums[j] )
                mx.pop_back();
            mx.push_back({nums[j],j});
        }
        // cout << "i " << i << endl;
        // finish up
        long long t = (n-i) * (n-i+1)/2;
        ans = ans + t;

        return ans;
    }
};
