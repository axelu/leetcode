
// 1189. Maximum Number of Balloons
// https://leetcode.com/problems/maximum-number-of-balloons/
// day 13 Sep 2021 challenge
// https://leetcode.com/explore/featured/card/september-leetcoding-challenge-2021/637/week-2-september-8th-september-14th/3973/





class Solution {
public:
    int maxNumberOfBalloons(string text) {
        int n = text.size();

        // 01234567890123456789012345
        // abcdefghijklmnopqrstuvwxyz
        // balloon: 1,0,11x2,14x2,13

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i)
            ++cnt[text[i]-'a'];

        int ans = INT_MAX;
        // b
        ans = min(ans,cnt[1]);
        // a
        ans = min(ans,cnt[0]);
        // l x2
        ans = min(ans,cnt[11]/2);
        // o x2
        ans = min(ans,cnt[14]/2);
        // n
        ans = min(ans,cnt[13]);


        return ans;
    }
};
