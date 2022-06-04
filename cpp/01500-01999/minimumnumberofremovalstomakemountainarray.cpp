
// 1671. Minimum Number of Removals to Make Mountain Array
// https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/




class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();

        // longest decreasing subsequence (LDS)
        // length of longest decreasing subsequence starting at idx i
        int lds[n];lds[n-1] = 1;

        for(int i = n-2; i >= 0; --i) {
            lds[i] = 1; // init to 1 at every index as there is at least the element itself
            for(int j = n-1; j > i; --j)
                if( nums[i] > nums[j] )
                    lds[i] = max(lds[i],lds[j]+1); // record length of longest decreasing subsequence
        }

        // longest increasing subsequence (LIS)
        // length of longest increasing subsequence ending at idx i
        int lis[n];lis[0] = 1;

        // it is guaranteed a mountain array can be formed out of nums.
        int lma = 3; // length of longest subsequence forming a mountain array (has to be at least 3)

        for(int i = 1; i < n-1; ++i) {
            lis[i] = 1; // init to 1 at every index as there is at least the element itself
            for(int j = 0; j < i; ++j) {
                if( nums[i] > nums[j] ) {
                    // record length of longest increasing subsequence
                    lis[i] = max(lis[i],lis[j]+1);
                }
            }
            // keep track of max LIS + LDS
            if( lis[i] > 1 && lds[i] > 1)
                lma = max(lma,lis[i]+(lds[i]-1));
        }

        return n-lma;
    }
};
