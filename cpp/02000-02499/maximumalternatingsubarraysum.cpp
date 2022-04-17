
// 2036. Maximum Alternating Subarray Sum
// https://leetcode.com/problems/maximum-alternating-subarray-sum/



class Solution {
public:
    long long maximumAlternatingSubarraySum(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];


        // 1 <= nums.length <= 10^5
        // -10^5 <= nums[i] <= 10^5
        // long should be sufficient max/min = 10^10 / -10^10


        // Kadane’s Algorithm
        // pass 1
        // convert numbers at odd indices to the negative version of that number,
        // then finding the maximum subarray sum for subarrays starting at even indices

	    long local_max = 0L;
	    long global_max = LONG_MIN;

        long long curr;
	    for(int i = 0; i < n; ++i) {
            if( i % 2 ) {       // odd index
                local_max = local_max - nums[i];
            } else {            // even index
                // we could start a new subarray or
                // continue the current subarray
                // it only makes sense to continue the current
                // subarray if local_max >= 0
                if( local_max < 0L )
                    local_max = nums[i];
                else
                    local_max += nums[i];
            }

            if( local_max > global_max )
			    global_max = local_max;
	    }

        // pass 2
        // convert numbers at even indices to the negative version of that number,
        // then finding the maximum subarray sum for subarrays starting at odd indices

	    local_max = 0L;

	    for(int i = 1; i < n; ++i) {
            if( i % 2 == 0 ) {      // even index
                local_max = local_max - nums[i];
            } else {                // odd index
                // we could start a new subarray or
                // continue the current subarray
                // it only makes sense to continue the current
                // subarray if local_max >= 0
                if( local_max < 0L )
                    local_max = nums[i];
                else
                    local_max += nums[i];
            }

            if( local_max > global_max )
			    global_max = local_max;
	    }

	    return global_max;
    }
};
