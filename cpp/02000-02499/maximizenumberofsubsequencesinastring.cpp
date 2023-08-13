
// 2207. Maximize Number of Subsequences in a String
// https://leetcode.com/problems/maximize-number-of-subsequences-in-a-string/





class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        int n = text.size();

        // it is always most beneficial
        //     to add pattern[0] in the very front OR
        //     to add pattern[1] at the very end
        // if count(pattern[0]) > count(pattern[1])
        //     then add pattern[1] to the end for a gain of count(pattern[0])
        //     else add pattern[0] to the front for a gain of count(pattern[1])

        long long ans = 0;

        if( pattern[0] != pattern[1] ) {
            long long cntp0 = 0;
            long long cntp1 = 0;
            for(int i = 0; i < n; ++i) {
                if( text[i] == pattern[0] ) {
                    ++cntp0;
                } else if( text[i] == pattern[1] ) {
                    ++cntp1;
                    ans += cntp0;
                }
            }
            if( cntp0 > cntp1 ) {
                ans += cntp0;
            } else {
                ans += cntp1;
            }

        } else { // pattern[0] == pattern[1]
            long long cntp = 1; // we can add pattern
            for(int i = 0; i < n; ++i)
                if( text[i] == pattern[0] )
                    ++cntp;

            ans = cntp * (cntp - 1)/2; // number of pairs: n(n - 1)/2
        }

        return ans;
    }
};
