
// 2871. Split Array Into Maximum Number of Subarrays
// https://leetcode.com/problems/split-array-into-maximum-number-of-subarrays/






/* example  0 1 2
 *          1 3 2
 * the min score we can get for any possible non-empty subarray is 0, with the array[0,2] inclusive
 * as that is the entire array, we return 1
 * example  0 1 2 3 4 5
 *          1 3 2 3 1 2
 * we return 2, because we can split array[0,2], array[3,5]
 * each subarray has a score of 0, so 0 + 0 = 0, which is minimum sum
 *
 * example  0 1
 *          3 1
 * min score is 1 of array[0,1], hence we return 1
 *
 * the score of an element byitself is the element
 */
class Solution {
public:
    int maxSubarrays(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        // key insight:
        //     minimum score will always be the bitwise AND of all elements

        int mn_score = nums[0];
        for(int x: nums)
            mn_score &= x;

        if( mn_score != 0 )
            return 1;

        int splits = 1;
        int score = nums[0];
        for(int i = 1; i < n; ++i) {
            if( score == 0 ) {
                ++splits;
                score = nums[i];
                continue;
            }
            score &= nums[i];
        }
        if( score != 0 )
            --splits;

        return splits;
    }
};
