
// 2845. Count of Interesting Subarrays
// https://leetcode.com/problems/count-of-interesting-subarrays/






/* example
 * nums = {6,6,6,6,5,6,6,5,6,5,6,5,6,6,5,6,6,6}, modulo = 3, k = 2 -> ans = 50
 *
 *                       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 n
 *                       6 6 6 6 5 6 6 5 6 5 6 5 6 6 5 6 6 6
 * nums[i] % modulo = k          x     x   x   x     x
 * gaps                  --------- ----- --- --- ----- -------
 *                         g0      g1    g2  g3   g4     g5
 *
 * ans = (g0 * g2) + (g1 * g3) + (g2 * g4) + (g3 * g5) + (g0 * g5)
 * ans = g0 * (g2 + g5) +                                          = 5 * (2 + 4) +
 *       g1 * (g3) +                                               = 3 * (2) +
 *       g2 * (g4) +                                               = 2 * (3) +
 *       g3 * (g5)                                                 = 2 * (4) +
 *                                                                 ---------------
 *                                                                   50
 */
class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();

        long long ans = 0LL;

        vector<long long> gaps;
        int last = -1;
        for(int i = 0; i < n; ++i) {
            if( nums[i] % modulo == k ) {
                int gap = i - last;
                gaps.push_back(gap);
                last = i;
            }
        }
        // finish up
        // if( last != -1 )
            gaps.push_back(n - last);
        //else
        //    gaps.push_back(n);

        int gaps_sz = gaps.size();
        //for(int i = 0; i < gaps_sz; ++i)
        //    cout << gaps[i] << " ";
        //cout << endl;

        long long suffixSum[gaps_sz];
        for(int i = gaps_sz - 1; i >= 0; --i) {
            suffixSum[i] = gaps[i];
            if( i + modulo < gaps_sz )
                suffixSum[i] += suffixSum[i + modulo];
        }
        //for(int i = 0; i < gaps_sz; ++i)
        //   cout << suffixSum[i] << " ";
        //cout << endl;

        // special handling for k = 0;
        int t = k == 0 ? modulo : k;
        for(int i = 0; i + t < gaps_sz; ++i) {
            ans = ans + gaps[i] * suffixSum[i+t];
        }

        // if k == 0 then any 'window' that does NOT include an element with nums[i] % modulo == k
        // is also an interesting subarray
        if( k == 0 ) {
            for(int i = 0; i < gaps_sz; ++i) {
                // formula for number of all subarrays : n  *  (n + 1)/2
                ans = ans + ( (gaps[i]-1) * gaps[i]/2);
            }
        }

        return ans;
    }
};
