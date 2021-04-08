
// 387. First Unique Character in a String
// https://leetcode.com/problems/first-unique-character-in-a-string/


class Solution {
public:
    int firstUniqChar(string s) {

        pair<int,int> cnt[26]; memset(cnt,0,sizeof cnt);
        for(int i = 0; i < s.size(); ++i) {
            ++cnt[s[i]-'a'].first;
            if( cnt[s[i]-'a'].first == 1 ) cnt[s[i]-'a'].second = i;
        }

        int ans = -1;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i].first == 1 )
                if( ans == -1 ) ans = cnt[i].second;
                else ans = min(ans,cnt[i].second);
        }
        return ans;
    }
};
