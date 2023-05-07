
// 2588. Count the Number of Beautiful Subarrays
// https://leetcode.com/problems/count-the-number-of-beautiful-subarrays/




/* based on provided hints in the problem
 *   A subarray is beautiful if its xor is equal to zero.
 *   Compute the prefix xor for every index
 *   xor of subarray [left, right] is equal to zero if prefix_xor[left] ^ perfix_xor[right] == 0
 *   Iterate from left to right and maintain a hash table to count the number of indices equal to the current prefix xor.
 * example
 *            0 1 2 3 4 5
 * nums       4 3 1 2 4
 * prefix_xor 0 4 7 6 4 0
 *    ans -> 2
 */
class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        int n = nums.size();

        int prefix_xor[n+1];
        prefix_xor[0] = 0;

        unordered_map<int,long long> um;
        um[0] = 1;

        long long ans = 0;

        for(int i = 1; i <= n; ++i) {
            prefix_xor[i] = prefix_xor[i-1] ^ nums[i-1];
            ans += um[prefix_xor[i]];
            ++um[prefix_xor[i]];
        }

        return ans;
    }
};
