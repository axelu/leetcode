
// 2527. Find Xor-Beauty of Array
// https://leetcode.com/problems/find-xor-beauty-of-array/




/*
 * Problem statement:
 *     The effective value of three indices i, j, and k is defined as ((nums[i] | nums[j]) & nums[k])
 *     The xor-beauty of the array is the XORing of the effective values of all the possible triplets
 *     of indices (i, j, k) where 0 <= i, j, k < n.
 *
 * Observations:
 * A:  self-inverse property of binary ^: a ^ a = 0 (https://accu.org/journals/overload/20/109/lewin_1915/)
 * B:  commutative property of binary & and | => a | b = b | a, a & b = b & a
 *
 * In the expression given ((nums[i] | nums[j]) & nums[k]),
 * let us fix index k:
 *   case: i != j
 *     (i,j,k), (j,i,k)  =>  ((nums[i] | nums[j]) & nums[k]) ^ ((nums[j] | nums[i]) & nums[k]) = 0
 *                            -------------------               -------------------
 *                            (nums[i] | nums[j])        =      (nums[j] | nums[i])
 *          so we basically end up at (a & b) ^ (a & b ) = 0
 *
 *  case: i == j
 *    (i,i,k)  =>  ((nums[i] | nums[i]) & nums[k]) = nums[i] & nums[k], which becomes (i,k),(k,i)
 *    if i != k:
 *        (nums[i] & nums[k]) ^ (nums[k] & nums[i]) = 0
 *    if i == k:
 *        ((nums[i] | nums[i]) & nums[i]) = nums[i] & nums[i] = nums[i]
 *
 * CONCLUSION:
 *   the only triplets of all possible triplets to consider are (i,i,i), for which the expression produces nums[i]
 *   hence we can simply compute xor of all elements
 */
class Solution {
public:
    int xorBeauty(vector<int>& nums) {

        int xorr = 0;
        for(int i = 0; i < nums.size(); ++i)
            xorr ^= nums[i];

        return xorr;
    }
};
