
// 2351. First Letter to Appear Twice
// https://leetcode.com/problems/first-letter-to-appear-twice/



class Solution {
public:
    char repeatedCharacter(string s) {
        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char c: s) {
            ++cnt[c-'a'];
            if( cnt[c-'a'] == 2 )
                return c;
        }

        return '#'; // satisfy compiler
    }
};
