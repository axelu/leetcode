
// 1160. Find Words That Can Be Formed by Characters
// https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/

class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {

        int chs[26]; memset(chs,0,sizeof chs);
        for(char c : chars) ++chs[c-'a'];

        size_t n;
        int r = 0;
        int i;
        int cnt[26];
        for(string s : words) {
            // reset cnt
            memset(cnt,0,sizeof cnt);

            n = s.size();
            for(i = 0; i < n; ++i) ++cnt[s[i]-'a'];

            for(i = 0; i < 26; ++i)
                if( cnt[i] > chs[i] ) break;
            if( i == 26 ) r += n;
        }
        return r;
    }
};
