
// 3223. Minimum Length of String After Operations
// https://leetcode.com/problems/minimum-length-of-string-after-operations/


class Solution {
public:
    int minimumLength(string s) {
        int cnt[26]; memset(cnt,0,sizeof cnt);
        for(char c: s)
            ++cnt[c-'a'];

        int ans = 0;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i] < 3 ) {
                ans += cnt[i];
            } else if( cnt[i] % 2 ) {
                ans += 1;
            } else {
                ans += 2;
            }
        }

        return ans;
    }
};
