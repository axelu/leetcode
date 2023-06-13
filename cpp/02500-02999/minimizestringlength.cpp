
// 2716. Minimize String Length
// https://leetcode.com/problems/minimize-string-length/




class Solution {
public:
    int minimizedStringLength(string s) {
        int cnt[26];memset(cnt,0,sizeof cnt);

        for(char c: s)
            ++cnt[c-'a'];

        int ans = 0;

        for(int i = 0; i < 26; ++i)
            if( cnt[i] )
                ++ans;

        return ans;
    }
};
