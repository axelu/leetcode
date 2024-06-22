
// 3090. Maximum Length Substring With Two Occurrences
// https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/




class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();

        int ans = 0;
        int freq[26];memset(freq,0,sizeof freq);

        // sliding window
        int i = 0;                  // left index
        for(int j = 0; j < n; ++j) {// right index
            int c = s[j] - 'a';
            ++freq[c];
            while( freq[c] == 3 ) {
                --freq[s[i] - 'a'];
                ++i;
            }

            int l = j - i + 1;
            ans = max(ans, l);
        }

        return ans;
    }
};
