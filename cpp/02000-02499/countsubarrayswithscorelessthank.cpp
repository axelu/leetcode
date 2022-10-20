
// 2302. Count Subarrays With Score Less Than K
// https://leetcode.com/problems/count-subarrays-with-score-less-than-k/




// see also 1918. Kth Smallest Subarray Sum
//     https://leetcode.com/problems/kth-smallest-subarray-sum/

class Solution {
private:
    long long na[100001]; // number of subarrays for a given length
    long long prefixSum[100001];

    long long solve(vector<int>& nums, int n, long long x) {
        // returns the number of subarrays with sum < x
        long long cnt = 0;
        int i = 0;       // left index
        int j = 0;       // right index
        int j_pre = 0;
        long long sum = 0;
        long long l;     // length of sliding window
        long long l_pre; // length of overlapping window
        for(; j < n; ++j) {
            l = j - i + 1;
            sum = (prefixSum[j+1] - prefixSum[i]) * l;
            if( sum >= x ) {
                l = j - i + 1;
                cnt += na[l-1];
                // don't double count
                // if we have an overlap with the prior window,
                // we subtract the number of subarrays in the overlapping window
                l_pre = j_pre - i + 1;
                if( l_pre > 0 )
                    cnt -= na[l_pre-1];

                while( sum >= x && i <= j) {
                    ++i;
                    --l;
                    sum = (prefixSum[j+1] - prefixSum[i]) * l;
                }
                j_pre = j;
            }
        }
        if( sum < x ) {
            l = j - i + 1;
            cnt += na[l-1];
            // don't double count
            l_pre = j_pre - i + 1;
            if( l_pre > 0 )
                cnt -= na[l_pre-1];
        }
        return cnt;
    }

public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        if( n == 1 )
            return nums[0] < k;

        // TODO deal with n <= 2

        na[0] = 0;
        for(long long i = 1; i < n+1; ++i)
            na[i] = na[i-1] + i;

        prefixSum[0] = 0;
        //prefixSum[1] = nums[0];
        //for(long long i = 2; i < n+1; ++i)
        //    prefixSum[i] = prefixSum[i-1] + prefixSum[i-1]/(i-1) + (long long)nums[i-1] * i;
        for(long long i = 1; i < n+1; ++i)
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];

        return solve(nums,n,k);
    }
};
