
// 2098. Subsequence of Size K With the Largest Even Sum
// https://leetcode.com/problems/subsequence-of-size-k-with-the-largest-even-sum/


/* cases if we had 2 numbers
 *     even + even = even
 *     even + odd  = odd
 *     odd  + even = odd
 *     odd  + odd  = even
 * this scales, meaning e.g. an even number of evens + an odd number of odds = odd, and so on
 */
class Solution {
public:
    long long largestEvenSum(vector<int>& nums, int k) {
        int n = nums.size();
        // edge cases
        if( n == 1 ) {
            return nums[0] % 2 ? -1 : nums[0];
        }
        if( n == k ) {
            long long sum = accumulate(nums.begin(),nums.end(),0LL);
            return sum % 2 ? -1 : sum;
        }

        // divide nums into evens and odds
        vector<long long> even;
        vector<long long> odd;
        for(int i = 0; i < n; ++i)
            if( nums[i] % 2 )
                odd.push_back(nums[i]);
            else
                even.push_back(nums[i]);

        sort(even.begin(),even.end(),greater<long long>());
        sort(odd.begin(),odd.end(),greater<long long>());

        int even_sz = even.size();
        int odd_sz = odd.size();

        int even_idx = 0;
        int odd_idx = 0;

        int even_cnt = 0;
        int odd_cnt = 0;

        long long t = 0;

        while( k > 0 ) {
            // pick the largest
            if( even_idx < even_sz && odd_idx < odd_sz ) {
                if( even[even_idx] > odd[odd_idx] ) {
                    t += even[even_idx];
                    ++even_idx;
                    ++even_cnt;
                } else {
                    t += odd[odd_idx];
                    ++odd_idx;
                    ++odd_cnt;
                }
            } else if( even_idx < even_sz ) {
                    t += even[even_idx];
                    ++even_idx;
                    ++even_cnt;
            } else { // odd_idx < odd_sz
                    t += odd[odd_idx];
                    ++odd_idx;
                    ++odd_cnt;
            }
            --k;
        }

        // end state
        //  nbr of   nbr of   result
        //  even     odd
        //  ------------------------
        //  even     even     even
        //  even     odd      odd
        //  odd      even     even
        //  odd      odd      odd

        long long sum = -1;

        if( odd_cnt % 2 ) {
            // back out an even number and replace with an odd OR
            // back out an odd number and replace with an even
            long long t1 = -1, t2 = -1;
            if( even_idx > 0 && odd_idx < odd_sz ) {
                t1 = t;
                t1 -= even[even_idx-1];
                t1 += odd[odd_idx];
            }
            if( odd_idx > 0 && even_idx < even_sz ) {
                t2 = t;
                t2 -= odd[odd_idx-1];
                t2 += even[even_idx];
            }
            sum = max(t1,t2);

        } else {
            // nothing to do
            sum = t;
        }

        return sum;
    }
};
