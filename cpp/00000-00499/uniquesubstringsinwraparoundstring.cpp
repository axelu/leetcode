
// 467. Unique Substrings in Wraparound String
// https://leetcode.com/problems/unique-substrings-in-wraparound-string/


// http://ruslanledesma.com/2016/12/10/unique-substrings-in-wraparound-string.html

class Solution {
public:
    int findSubstringInWraproundString(string p) {
        long n = p.size();

        int cnt[26];memset(cnt,0,sizeof cnt);

        char prevChar = '#';
        int t;
        for(int i = 0; i < n; ++i) {
            if( prevChar + 1 == p[i] || (prevChar == 'z' && p[i] == 'a') ) {
                ++t;
            } else {
                t = 1;
            }
            cnt[p[i]-'a'] = max(cnt[p[i]-'a'],t);
            prevChar = p[i];
        }

        int ans = 0;
        for(int i = 0; i < 26; ++i)
            ans += cnt[i];

        return ans;
    }
};
