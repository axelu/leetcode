
// 918. Maximum Sum Circular Subarray
// https://leetcode.com/problems/maximum-sum-circular-subarray/

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();

        if( n == 1 )
            return nums[0];

        if( n == 2 )
            return max({nums[0],nums[1],nums[0]+nums[1]});

        // Kadane’s Algorithm plus
	    int local_max   = nums[0];
	    int global_max  = nums[0]; // Kadane's max

        // keep track of max [0,i] inclusive
        int prefix_max[n];
        prefix_max[0]   = nums[0];
        int sum         = nums[0];

	    for(int i = 1; i < n; ++i) {
		    local_max = max(nums[i], nums[i] + local_max);
		    if( local_max > global_max )
			    global_max = local_max;

            sum += nums[i];
            prefix_max[i] = max(prefix_max[i-1],sum);
	    }


	    // reverse
        // keep track of max [i,n-1] inclusive
        int suffix_max[n];
        suffix_max[n-1] = nums[n-1];
        int rsum        = nums[n-1];

        int circular_max = INT_MIN;

        for(int i = n-2; i > 0; --i) {
            circular_max = max(circular_max,suffix_max[i+1]+prefix_max[i-1]);

            rsum += nums[i];
            suffix_max[i] = max(suffix_max[i+1],rsum);
        }

        return max(global_max,circular_max);
    }
};
