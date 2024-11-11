
// 3325. Count Substrings With K-Frequency Characters I
// https://leetcode.com/problems/count-substrings-with-k-frequency-characters-i/




class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.size();

        int ans = 0;

        int cnt[26];memset(cnt,0,sizeof cnt);

        // sliding window
        int last_start = -1;
        int i = 0;
        for(int j = 0; j < n; ++j) {
            int c = s[j]-'a';
            ++cnt[c];
            if( cnt[c] == k ) {
                while( s[i] != s[j] ) {
                    --cnt[s[i]-'a'];
                    ++i;
                }

                ans = ans + ((n-j) *(i+1));
                // don't doublecount
                if( last_start != -1 )
                    ans = ans - ((last_start+1) * (n-j));
                last_start = i;
                --cnt[s[i]-'a'];
                ++i;
            }

        }

        return ans;
    }
};
