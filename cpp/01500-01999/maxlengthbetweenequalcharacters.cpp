
// 1624. Largest Substring Between Two Equal Characters
// https://leetcode.com/problems/largest-substring-between-two-equal-characters/


class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        auto n = s.size();
        if( n == 1 ) return -1;

        int firstseen[26]; memset(firstseen,-1,sizeof firstseen);
        int lastseen[26]; memset(lastseen,-1,sizeof lastseen);

        int r = 0;
        for(int i = 0; i < n; ++i) {
            char ch = s[i] - 'a';
            if( firstseen[ch] == -1 ) firstseen[ch] = i;
            lastseen[ch] = i;
            r = max(r,lastseen[ch] - firstseen[ch]);
        }

        /*
        int r = 0;
        for(int i = 0; i < 26; ++i)
            r = max(r,lastseen[i] - firstseen[i]);
        */

        return r == 0 ? -1 : r-1;
    }
};
