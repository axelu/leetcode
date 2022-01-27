
// 771. Jewels and Stones
// https://leetcode.com/problems/jewels-and-stones/


class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        int cnt[52]; memset(cnt,0,sizeof cnt); // abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ

        int cntIdx;
        for(int i = 0; i < stones.size(); ++i)
            if( stones[i] >= 97 ) ++cnt[stones[i]-'a'];
            else ++cnt[stones[i]-'A'+26];

        int ans = 0;
        for(int i = 0; i < jewels.size(); ++i)
            if( jewels[i] >= 97 ) ans += cnt[jewels[i]-'a'];
            else ans += cnt[jewels[i]-'A'+26];

        return ans;
    }
};
