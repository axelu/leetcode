
// 1876. Substrings of Size Three with Distinct Characters
// https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/



class Solution {
public:
    int countGoodSubstrings(string s) {
        int n = s.size();
        if( n < 3 ) return 0;

        int ans = 0;

        int cnt[26];memset(cnt,0,sizeof cnt);
        int d = 0, l = 0;
        for(int i = 0; i < n; ++i) {
            if( ++cnt[s[i]-'a'] == 1 )
                ++d;

            if( i-l < 2 )
                continue;

            if( d == 3 )
                ++ans;

            if( --cnt[s[l]-'a'] == 0 )
                --d;
            ++l;
        }

        return ans;
    }
};
