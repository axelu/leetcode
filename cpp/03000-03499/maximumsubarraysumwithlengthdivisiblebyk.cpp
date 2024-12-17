
// 3381. Maximum Subarray Sum With Length Divisible by K
// https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/





class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= nums.length <= 2 * 1e5

        vector<long long> prefixSum(n+1);
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];

        long long ans = LLONG_MIN;

        // Kadane max subarray sum

        for(int rem = 0; rem < k && rem+k <= n; ++rem) {


            long long local_max = prefixSum[rem+k] - prefixSum[rem];
            long long global_max = prefixSum[rem+k] - prefixSum[rem];

            for(int i = rem + k; i < n; i += k) {
                if( i + k > n )
                    break;


                long long a = prefixSum[i+k] - prefixSum[i];

                local_max = max(a, a + local_max);
                if( local_max > global_max )
                    global_max = local_max;
            }

            ans = max(ans, global_max);
        }

        return ans;
    }
};
