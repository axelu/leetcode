
// 2730. Find the Longest Semi-Repetitive Substring
// https://leetcode.com/problems/find-the-longest-semi-repetitive-substring/




class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int n = s.size();

        int ans = 0;
        int cnt = 0; // count of consecutive pairs of the same digit

        // sliding window
        int i = 0;
        for(int j = 0; j < n; ++j) {

            if( j > 0 && s[j-1] == s[j] )
                ++cnt;

            while( cnt > 1 && i < j ) {
                if( s[i] == s[i+1] )
                    --cnt;
                ++i;
            }

            ans = max(ans, j-i+1);
        }

        return ans;
    }
};
