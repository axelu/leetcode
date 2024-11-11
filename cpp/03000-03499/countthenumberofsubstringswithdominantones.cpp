
// 3234. Count the Number of Substrings With Dominant Ones
// https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/





class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (s[i-1] - '0');

        int ans = 0;

        for(int i = 0; i < n; ++i) {
            for(int j =  i; j < n; ++j) {
                int ones = prefixSum[j+1] - prefixSum[i];
                int zeros = (j - i + 1) - ones; // length_of_substring - ones

                if( ones >= zeros * zeros ) {
                    // we have enough ones
                    ++ans;

                    if( ones > zeros * zeros ) {
                        // we even have a surplus of ones and hence can make a jump to consume the surplus
                        int ones_needed = sqrt(ones);
                        int jump = ones_needed - zeros;
                        int j_new = j + jump;

                        if( j_new >= n )
                            ans += (n - j - 1); // all remaining subarrays meet the condition
                        else
                            ans += jump;        // all subarrays till where we can jump to meet the condition

                        j = j_new;
                    }

                } else {
                    // we don't have enough ones
                    // so we need to jump forward by at least the shortfall of ones
                    int jump = (zeros * zeros) - ones;
                    j += jump;
                    --j; // loop will advance j
                }
            }
        }

        return ans;
    }
};
