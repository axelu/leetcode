
// 1191. K-Concatenation Maximum Sum
// https://leetcode.com/problems/k-concatenation-maximum-sum/




// see also
// 53. Maximum Subarray https://leetcode.com/problems/maximum-subarray/
// 918. Maximum Sum Circular Subarray https://leetcode.com/problems/maximum-sum-circular-subarray/

class Solution {
private:
    int maxSubArray(vector<int>& nums) {
        // Kadane’s Algorithm

	    int n = nums.size();
	    int local_max = 0;
	    int global_max = INT_MIN;

	    for(int i = 0; i < n; ++i) {
		    local_max = max(nums[i], nums[i] + local_max);
		    if( local_max > global_max )
			    global_max = local_max;
	    }

	    return global_max;
    }

public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        int n = arr.size();
        if( n == 1 )
            return arr[0] > 0 ? k * arr[0] : 0;

        int max_subarray = maxSubArray(arr);
        if( k == 1 )
            return max(max_subarray,0);

        // max prefix
        // keep track of max [0,i] inclusive
        long prefix_max = arr[0];
        long sum        = arr[0];
	    for(int i = 1; i < n; ++i) {
            sum += arr[i];
            prefix_max = max(prefix_max,sum);
	    }

	    // reverse, max suffix
        // keep track of max [i,n-1] inclusive
        long suffix_max = arr[n-1];
        long rsum       = arr[n-1];
        for(int i = n-2; i >= 0; --i) {
            rsum += arr[i];
            suffix_max = max(suffix_max,rsum);
        }

        // the answer is the maximum of:
        //     - the answer for k=1, or
        //     - the sum of the whole array multiplied by k, or
        //     - the maximum suffix sum plus the maximum prefix sum for k > 1, or
        //     - the maximum suffix sum plus the maximum prefix sum plus (k-2) multiplied
        //        by the whole array sum for k > 1

        long a = max_subarray;
        long b = sum * k;
        long c = suffix_max + prefix_max;
        long d = suffix_max + sum * (k-2) + prefix_max;

        return max({a,b,c,d,0L}) % 1000000007;
    }
};
