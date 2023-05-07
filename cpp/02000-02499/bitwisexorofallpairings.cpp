
// 2425. Bitwise XOR of All Pairings
// https://leetcode.com/problems/bitwise-xor-of-all-pairings/


/*                2^4  2^3  2^2  2^1  2^0
 *                 16    8    4    2    1
 * binary 5                   1    0    1
 * if repeated 2 times => 0 <= 5 ^ 5      even number times
 * if repeated 3 times => 5 <= 5 ^ 5 ^ 5  odd  number times
 * example nums1 = {5}, nums2 = {10,2,7}
 *   => 5 ^ 10 ^ 2 ^ 7
 *
 *           nums1.size()  nums2.size()
 *           even          even         => 0
 *           even          odd          => XOR of all nums1 elements
 *           odd           odd          => XOR of all elements
 *           odd           even         => XOR of all nums2 elements
 */
class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();

        int ans = 0;

        /*
        // brute force
        vector<int> nums3;
        for(int i = 0; i < n1; ++i) {
            for(int j = 0; j < n2; ++j) {
                nums3.push_back(nums1[i]^nums2[j]);
            }
        }
        for(int k = 0; k < nums3.size(); ++k)
            ans = ans ^ nums3[k];
        */

        if( n1 % 2 == 0 && n2 % 2 == 1 ) {
            for(int i = 0; i < n1; ++i)
                ans = ans ^ nums1[i];
        } else if( n1 % 2 == 1 && n2 % 2 == 1 ) {
            for(int i = 0; i < n1; ++i)
                ans = ans ^ nums1[i];
            for(int i = 0; i < n2; ++i)
                ans = ans ^ nums2[i];
        } else if( n1 % 2 == 1 && n2 % 2 == 0 ) {
            for(int i = 0; i < n2; ++i)
                ans = ans ^ nums2[i];
        }

        return ans;
    }
};
