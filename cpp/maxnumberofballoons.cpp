
// 1189. Maximum Number of Balloons
// https://leetcode.com/problems/maximum-number-of-balloons/


class Solution {
public:
    int maxNumberOfBalloons(string text) {
        auto n = text.size();
        if( n < 7 ) return 0;

        int cnt[26]; memset(cnt,0,sizeof cnt);
        for(auto it = begin(text); it != end(text); ++it)
            ++cnt[*it - 'a'];

        int r = min(cnt[11]/2,cnt[14]/2);   // l and o
        r = min({r,cnt[0],cnt[1],cnt[13]}); // a,b,n
        return r;
    }
};
