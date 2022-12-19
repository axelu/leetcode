
// 2423. Remove Letter To Equalize Frequency
// https://leetcode.com/problems/remove-letter-to-equalize-frequency/


class Solution {
public:
    bool equalFrequency(string word) {
        int cnt[26];memset(cnt,0,sizeof cnt);

        for(char c: word)
            ++cnt[c-'a'];

        int mn = 100;
        int mn_cnt = 0;
        int mx = 0;
        int mx_cnt = 0;
        int unique_cnt = 0;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i] > 0 ) {
                ++unique_cnt;
                if( cnt[i] < mn ) {
                    mn = cnt[i];
                    mn_cnt = 1;
                } else if( cnt[i] == mn ) {
                    ++mn_cnt;
                }
            }
            if( cnt[i] > mx ) {
                mx = cnt[i];
                mx_cnt = 1;
            } else if( cnt[i] == mx )
                ++mx_cnt;

        }

        //cout << "unique_cnt " << unique_cnt << endl;
        //cout << "mn " << mn << " mx " << mx << endl;
        //cout << " mn_cnt " << mn_cnt << " mx_cnt " << mx_cnt << endl;

        int n = word.size();
        if( (unique_cnt == 1) ||                        // aaaaaa
            (mn == 1 && mx == 1) ||                     // abc
            (mn == 1 && mx_cnt * mx == n-1)  ||         // aaabbbc
            (mn_cnt * mn == n-mx && mx - mn == 1) )     // aaabbbcccc
            return true;

        return false;
    }
};
