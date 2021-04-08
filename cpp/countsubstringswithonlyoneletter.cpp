
// 1180. Count Substrings with Only One Distinct Letter
// https://leetcode.com/problems/count-substrings-with-only-one-distinct-letter/



class Solution {
public:
    int countLetters(string S) {
        size_t n = S.size();
        if( n == 1 ) return 1;

        int ans = 0;
        int t = 1; // lenght of curr substring with only one char
        char prev = S[0];
        for(int i = 1; i < n; ++i) {
            if( S[i] == prev ) {
                ++t;
            } else {
                // https://en.wikipedia.org/wiki/Arithmetic_progression#Sum
                ans += (1 + t) * t / 2;
                prev = S[i];
                t = 1;
            }
        }
        ans += (1 + t) * t / 2;
        return ans;
    }
};
