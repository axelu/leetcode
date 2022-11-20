
// 523. Continuous Subarray Sum
// https://leetcode.com/problems/continuous-subarray-sum/




/* example
 * let k = 7
 * examples where nums[2,5] inclusive sums up to a multiple of 7
 *                0   1   2   3   4   5
 * nums           9   1   7   3   4
 * prefixSum      0   9  10  17  20  24
 * prefixSum % k  0   2   3   3   6   3
 *
 * nums           9   3   7   3   4
 * prefixSum      0   9  12  19  22  26
 * prefixSum % k  0   2   5   5   6   5
 *
 * nums           9   1   7   2   5
 * prefixSum      0   9  10  17  19  24
 * prefixSum % k  0   2   3   3   5   3
 *
 * observation: if at a given index i, we have seen prefixSum[i] % k at
 *              an index j < i-1 before, then there is a continuous subarray
 *              of at least two elements that is a multiple of k
*/
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        unordered_map<int,int> first_seen;
        first_seen.insert({0,0});

        for(int i = 1; i <= n; ++i) {

            prefixSum[i] = prefixSum[i-1] + nums[i-1];
            int rem = prefixSum[i] % k;

            auto f = first_seen.insert({rem,i});
            if( f.first->second < i-1 )
                return true;
        }

        return false;
    }
};
