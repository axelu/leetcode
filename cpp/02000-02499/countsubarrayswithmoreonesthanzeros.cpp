
// 2031. Count Subarrays With More Ones Than Zeros
// https://leetcode.com/problems/count-subarrays-with-more-ones-than-zeros/



class Solution {
public:
    int subarraysWithMoreZerosThanOnes(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 10^5

        long MOD = 1000000007;

        // let us use i as left index and j as right index
        // if the current position j is a 1, then all subarrays that end
        // at j-1 and sum up to 0 become valid.
        // these subarrays that sum up to 0 ending at j-1 can start
        // at any arbitrary index i, the question is: how many are there?
        // if the sum[0,j] is x, then any subarray [i,j-1] with a sum of 0
        // means, that there is a subarray [0,i] that sums to x-1
        // so we count how many times we have sum x-1.

        unordered_map<int,long> um; // prefixSum,count
        um[0] = 1L;

        int prefixSum = 0; // don't need a prefix sum array as we don't access it after the fact
        long ans = 0;
        long cnt = 0;
        for(int j = 0; j < n; ++j) {
            if( nums[j] == 0 ) {
                cnt = (cnt - um[prefixSum-1]) % MOD;
                --prefixSum;
            } else {
                cnt = (cnt + um[prefixSum]) % MOD;
                ++prefixSum;
            }
            ++um[prefixSum];
            ans = (ans + cnt) % MOD;

        }

        return ans;
    }
};
