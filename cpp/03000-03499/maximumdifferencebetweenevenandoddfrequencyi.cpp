
// 3442. Maximum Difference Between Even and Odd Frequency I
// https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/





class Solution {
public:
    int maxDifference(string s) {
        int n = s.size();

        int cnt[26];memset(cnt,0,sizeof cnt);

        for(int i = 0; i < n; ++i)
            ++cnt[s[i]-'a'];

        // max difference = frequency character with an odd frequency minus
        //                  frequency of character with an even frequency

        int mx_odd = 0;
        int mn_even = INT_MAX;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i] > 0 ) {
                if( cnt[i] % 2 )
                    mx_odd = max(mx_odd, cnt[i]);
                else
                    mn_even = min(mn_even, cnt[i]);
            }
        }

        return mx_odd - mn_even;
    }
};
