
// 396. Rotate Function
// https://leetcode.com/problems/rotate-function/


class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        long n = nums.size();

        if( n == 1 )
            return 0;
        if( n == 2 )
            return max(nums[0],nums[1]);

        long prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + (long)nums[i];


        long rs = 0;
        // special treatment 0 at index 0
        for(long i = 1; i < n; ++i)
            rs += i * (long)nums[i];

        long ans = rs;

        // special treatment 0 at index n-1
        rs = 0;
        for(long i = 0; i < n-1; ++i)
            rs += (i+1) * (long)nums[i];

        ans = max(ans,rs);

        for(long i = n-2; i > 0; --i) {
            rs = rs - ((n-1) * (long)nums[i]) + prefixSum[i] + (prefixSum[n] - prefixSum[i+1]);
            ans = max(ans,rs);
        }

        return ans;
    }
};
