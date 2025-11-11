
// 3713. Longest Balanced Substring I
// https://leetcode.com/problems/longest-balanced-substring-i/


class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        if( n == 1 )
            return 1;

        // brute force
        int cnt[26];
        int freq[1001];
        int freqcnt, i, j, curr_cnt, old_cnt;
        for(int l = n; l >= 2; --l) {

            memset(cnt,0,sizeof cnt);
            memset(freq,0,sizeof freq);
            freqcnt = 0;

            i = 0;
            for(j = 0; j < n; ++j) {
                curr_cnt = cnt[s[j]-'a'];
                if( curr_cnt != 0 ) {
                    --freq[curr_cnt];
                    if( freq[curr_cnt] == 0 )
                        --freqcnt;
                }
                ++cnt[s[j]-'a'];
                ++freq[curr_cnt+1];
                if( freq[curr_cnt+1] == 1 )
                    ++freqcnt;

                if( j-i+1 == l ) {
                    if( freqcnt == 1 )
                        return l;

                    old_cnt = cnt[s[i]-'a'];
                    --freq[old_cnt];
                    if( freq[old_cnt] == 0 )
                        --freqcnt;

                    --cnt[s[i]-'a'];
                    if( old_cnt > 1 ) {
                        ++freq[old_cnt-1];
                        if( freq[old_cnt-1] == 1 )
                            ++freqcnt;
                    }

                    ++i;
                }
            }
        }

        return 1;
    }
};
