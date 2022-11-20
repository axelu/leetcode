
// 2222. Number of Ways to Select Buildings
// https://leetcode.com/problems/number-of-ways-to-select-buildings/



class Solution {
public:
    long long numberOfWays(string& s) {
        int n = s.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (s[i-1]-'0');

        long long ans = 0;

        for(int i = 1; i < n-1; ++i) {
            if( s[i] == '0' ) {
                // number of 1s before index i
                long long a = prefixSum[i];
                // number of 1s after index i
                long long b = prefixSum[n] - prefixSum[i+1];

                ans += a * b;

            } else { // s[i] == '1'
                // number of 0s before index i
                long long a = i - prefixSum[i];
                // number of 0s after index i
                long long b = (n-1-i) - (prefixSum[n] - prefixSum[i+1]);

                ans += a * b;
            }
        }

        return ans;
    }
};
