
// 3139. Minimum Cost to Equalize Array
// https://leetcode.com/problems/minimum-cost-to-equalize-array/






/* example [1,14,14,15], cost1 = 2, cost2 = 1
 * the best solution is to increase all to 21
 */
class Solution {
private:
    const long mod = 1000000007;

public:
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        // if cost2 <  2 * cost1 it is most beneficial to do as many type2 operations as possible
        // if cost2 >= 2 * cost1 we use cost 1

        long mn  = 1000000L;
        long mx  = 0L;
        long sum = 0L;
        for(long x: nums) {
            mn = min(mn,x);
            mx = max(mx,x);
            sum += x;
        }

        if( n == 2 )
            return ((long)(mx - mn) * cost1) % mod;

        long ans;

        if( cost2 >= 2 * cost1 ) {
            ans = ((mx * n - sum) * cost1) % mod;

        } else {

            ans = LLONG_MAX;

            // let us increase the max element up to 2 x mx and return the best answer
            for(long mx_element = mx;  mx_element < mx * 2; ++mx_element) {

                long diff  = (mx_element * n) - sum;
                long mn2mx = mx_element - mn;

                // we can form pairs up to the diff/2 OR
                // the diff between the min element and the current max we are aiming at, but not more
                long nbr_pairs = min(diff/2, diff - mn2mx);

                // we either take a pair * cost2, or we take two elements time cost1
                long cost = min(nbr_pairs * cost2, nbr_pairs * 2 * cost1);
                cost = cost + ((diff - (nbr_pairs * 2)) * cost1); // if there is a non-pair left

                ans = min(ans, cost);
            }
        }

        return ans % mod;
    }
};
