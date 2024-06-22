
// 3016. Minimum Number of Pushes to Type Word II
// https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/





class Solution {
public:
    int minimumPushes(string& word) {
        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char c: word)
            ++cnt[c-'a'];

        multiset<int> freq;
        for(int i = 0; i < 26; ++i)
            if( cnt[i] != 0 )
                freq.insert(cnt[i]);

        int ans = 0;

        int i = 0;
        int presses = 0;
        for(auto it = freq.rbegin(); it != freq.rend(); ++it) {
            if( i % 8 == 0 ) // we are mapping onto 8 keys
                ++presses;

            ans += presses * *it;
            ++i;
        }

        return ans;
    }
};
