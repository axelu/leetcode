
// 1524. Number of Sub-arrays With Odd Sum
// https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/



class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return arr[0] % 2 ? 1 : 0;

        long mod = 1000000007;

        // even + even = even
        // odd  + odd  = even
        // even + odd  = odd
        // odd  + even = odd

        long odp[n]; // number of odd  subarray's ending at i
        long edp[n]; // number of even subarray's ending at i
        odp[0] = arr[0] % 2 ? 1L : 0L;
        edp[0] = !odp[0];
        long ans = odp[0];
        for(int i = 1; i < n; ++i) {
            if( arr[i] % 2 == 0 ) { // even
                odp[i] = odp[i-1];
                ans = (ans + odp[i-1]) % mod;
                edp[i] = (edp[i-1] + 1) % mod;
            } else {                // odd
                odp[i] = (edp[i-1] + 1) % mod;
                ans = (ans + edp[i-1] + 1) % mod;
                edp[i] = odp[i-1];
            }
        }

        return ans;
    }
};
