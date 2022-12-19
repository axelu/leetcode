
// 2287. Rearrange Characters to Make Target String
// https://leetcode.com/problems/rearrange-characters-to-make-target-string/




class Solution {
public:
    int rearrangeCharacters(string s, string target) {
        int cnt_target[26];memset(cnt_target,0,sizeof cnt_target);
        for(char c: target)
            ++cnt_target[c-'a'];

        int cnt_s[26];memset(cnt_s,0,sizeof cnt_s);
        for(char c: s)
            ++cnt_s[c-'a'];

        int ans = INT_MAX;
        for(int i = 0; i < 26; ++i)
            if( cnt_target[i] > 0 )
                ans = min(ans,cnt_s[i]/cnt_target[i]);

        return ans;
    }
};
