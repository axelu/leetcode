
// 2875. Minimum Size Subarray in Infinite Array
// https://leetcode.com/problems/minimum-size-subarray-in-infinite-array/




class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        int n = nums.size();

        long prefixSum[n+1];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i-1] + nums[i-1];
        }
        /*
        for(int i = 0; i <= n; ++i)
            cout << i << ":" << prefixSum[i] << " ";
        cout << endl;
        */

        // let S be the sum of all elements in nums;
        // S = prefixSum[n];
        // if target <= S, then
        //     org arr      -----
        //     1 wrap       -----|-----
        //                  ++              ans is a prefix
        //                     ++           ans is a suffix
        //                   ++             ans is somewhere in the middle
        //                      +|+         ans is a wrap (suffix + prefix)
        // if target > S, then
        //     ans cannot be somewhere in the middle

        int res = n+1;
        int m = target / prefixSum[n];

        int t = target - (m *prefixSum[n]);
        // cout << "t " << t << endl;

        // sliding window
        long sum = 0;
        int i = 0;  // left index
        for(int j = 0; j < 2*n; ++j) {
            if( j >= n && i >= n )
                break;

            int jidx = j % n;
            sum = sum + nums[jidx];

            while( sum > t ) {
                int iidx = i % n;
                sum = sum - nums[iidx];
                ++i;
            }
            if( sum == t ) {
                res = min(res, j - i + 1);
            }
        }

        if( res == n+1 )
            return -1;

        return (m * n) + res;
    }
};
