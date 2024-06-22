
// 3022. Minimize OR of Remaining Elements Using Operations
// https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/





/* let us envision our nums as a matrix, where the rows are the bits
 * example nums[13,19]
 *         0    1      AND
 *        13   19
 * 2^0     1    1
 * 2^1     0    1
 *   2     1    0
 *   3     1    0
 *   4     0    1
 * observations
 *     it is benficial to attack the highest set bit among all nums[i] (highest row with sum of set bits > 1, most significant bit)
 *     if the sum of set bits in a given row is 0 or 1, we don't need to worry about that row
 *     let number of set bits in a row be t (t > 1), it will take t-1 operations to get it down to 1 set bit
 *     there has to be at least one 0 in the row to be able to eliminate set bits
 *     unless we are able to get the set bits in a row down to 1, don't waste operations on that row
 */
class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;

        // edge case
        if( k == 0 ) {
            ans = nums[0];
            for(int i = 0; i < n; ++i)
                ans |= nums[i];

            return ans;
        }

        // we can apply between 0 to k operations
        // 0 <= nums[i] < 2^30  <- 30bits 0-29 to check

        for(int i = 29; i >= 0; --i) { // bit

            int ops = 0; // operations count
            int mask = ans | (1<<i); // by carrying forward what we already have determined to set in ans
                                     // we are ensuring that we are not rolling back the impact of a more significant bit

            for(int j = 0; j < n; ++j) {

                if( (mask & nums[j]) == 0 )
                    continue;

                // how many consecutive nums[i] do we have where we can set the bits in our mask?
                int s = j; // remember where we where
                while( j < n && (mask & nums[j]) != 0 ) {
                    mask = mask & nums[j];
                    ++j;

                }

                ops += j - s;
                mask = ans | (1<<i); // resetting our mask
            }

            if( ops <= k )
                ans = ans | (1<<i);

        }


        int a = pow(2,30) - 1;
        return a ^ ans;
    }
};
