
// 2505. Bitwise OR of All Subsequence Sums
// https://leetcode.com/problems/bitwise-or-of-all-subsequence-sums/




class Solution {
public:
    long long subsequenceSumOr(vector<int>& nums) {
        // the set bits of all elements in nums will be set
        //   if we do OR of sum of all subsequences, as each element
        //   byitself is a subsequence
        // also, because we are summing, the set bits of each sum of a given subseqence
        //   will be covered by the set bits of all prefixSums

        int n = nums.size();

        long long ans = 0LL;

        long long prefixSum[n+1];
        prefixSum[0] = 0LL;
        for(int i = 0; i < n; ++i) {
            ans |= nums[i];
            prefixSum[i+1] = prefixSum[i] + nums[i];
            ans |= prefixSum[i+1];
        }

        return ans;
    }
};
