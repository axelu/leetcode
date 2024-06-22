
// 3138. Minimum Length of Anagram Concatenation
// https://leetcode.com/problems/minimum-length-of-anagram-concatenation/




class Solution {
public:
    int minAnagramLength(string s) {
        // all letters that occur in s must be in the substring t
        // length of s must be a multiple of lenght of t, let that multiple be x
        // number of occurences of each char in t * x must equal the number of each char in s
        // at that point of have a candidate t that we need to verify

        int n = s.size();

        int prefixSum[n+1][26];
        for(int j = 0; j < 26; ++j)
            prefixSum[0][j] = 0;

        for(int i = 1; i <= n; ++i) {
            int c = s[i-1] - 'a';
            prefixSum[i][c] = prefixSum[i-1][c] + 1;

            for(int j = 0; j < 26; ++j) {
                if( j == c )
                    continue;
                prefixSum[i][j] = prefixSum[i-1][j];
            }
        }


        for(int i = 0; i < n-1; ++i) {
            if( n % (i+1) == 0 ) {

                int x = n / (i+1);
                auto is_candidate = true;
                for(int j = 0; j < 26; ++j) {
                    if( prefixSum[i+1][j] * x != prefixSum[n][j] ) {
                        is_candidate = false;
                        break;
                    }
                }
                if( is_candidate ) {
                    for(int f = 2; f < x; ++f) {
                        int idx = f * (i+1);
                        for(int j = 0; j < 26; ++j) {
                            if( prefixSum[i+1][j] * f != prefixSum[idx][j] ) {
                                is_candidate = false;
                                break;
                            }
                        }
                    }
                }
                if( is_candidate )
                    return i + 1;
            }
        }

        return n; // we should never get here
    }
};
