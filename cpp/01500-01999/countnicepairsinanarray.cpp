
// 1814. Count Nice Pairs in an Array
// https://leetcode.com/problems/count-nice-pairs-in-an-array/



/* example 42,97
 *   97 -> rev(97) = 79 -> diff org - rev = 97 - 79 = 18
 *   42 -> rev(42) = 24 -> diff org - rev = 42 - 24 = 18
 *
 * example 24,79
 *   79 -> rev(79) = 97 -> diff org - rev = 79 - 97 = -18
 *   24 -> rev(24) = 42 -> diff org - rev = 24 - 42 = -18
 */
class Solution {
private:
    long reverse_int(int x) {
        // x is non-negative integer
        long ret = 0;
        while( x > 0 ) {
            ret = ret * 10 + (x % 10);
            x /= 10;
        }
        return ret;
    }

public:
    int countNicePairs(vector<int>& nums) {
        int n = nums.size();

        long mod = 1000000007;
        long ans = 0;
        unordered_map<long,long> um;

        for(int i = 0; i < n; ++i) {
            long org = nums[i];
            long rev = reverse_int(org);
            long diff = org - rev;

            ans = (ans + um[diff]) % mod;

            ++um[diff];
        }

        return ans;
    }
};
