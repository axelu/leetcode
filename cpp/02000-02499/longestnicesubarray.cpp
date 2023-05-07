
// 2401. Longest Nice Subarray
// https://leetcode.com/problems/longest-nice-subarray/




/*
 * example
 *  0  1  2  3  4
 *  1  3  8 48 10
 *  longest nice subarray 3,8,48 because
 *    3 AND 8 = 0.
 *    3 AND 48 = 0.
 *    8 AND 48 = 0.
 * observation
 *    as long as the sum of elements in a sliding window matches the XOR or the elements in the window
 *        the AND of the elements in the window is null
 *    if we hit the case that the sum does no longer match the XOR we need to shorten the window
 *        till XOR and sum match again by taking XOR for the element we are removing
 * example
 *   3  8 48 12
 *   window with 3,8,48: XOR 3 ^ 8 ^ 48 = 59, SUM 3 + 8 + 48 = 59
 *   window with 3,8,48,12: XOR 3 ^ 8 ^ 48 ^ 1 = 55, SUM 3 + 8 + 48 + 12 = 71   <= no good
 *   now we can reduce window size till SUM and XOR or all elements match again
 *      window with 8,48,12: XOR (3 ^ 8 ^ 48 ^ 12) ^ 3 = 52   SUM (3 + 8 + 48 + 12) - 3 = 68
 *      window with 48,12: XOR (3 ^ 8 ^ 48 ^ 12) ^ 3 ^ 8 = 60   SUM (3 + 8 + 48 + 12) - 3 - 8 = 60
 */

class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        int ans = 1;

        // sliding window

        int _xor = 0;
        int _sum = 0;
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index

            _xor = _xor ^ nums[j];
            _sum = _sum + nums[j];

            if( _xor == _sum ) {
                int l = j - i + 1;
                ans = max(ans,l);

            } else {
                // we need to shrink the window

                while( _xor != _sum ) {
                    _xor = _xor ^ nums[i];
                    _sum = _sum - nums[i];
                    ++i;
                }
            }
        }


        return ans;
    }
};
