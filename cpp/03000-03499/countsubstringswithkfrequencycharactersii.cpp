
// 3329. Count Substrings With K-Frequency Characters II
// https://leetcode.com/problems/count-substrings-with-k-frequency-characters-ii/





class Solution {
public:
    long long numberOfSubstrings(string s, int k) {
        long long n = s.size();

        long long ans = 0;

        int cnt[26];memset(cnt,0,sizeof cnt);

        // sliding window
        long long last_start = -1;
        long long i = 0;
        for(long long j = 0; j < n; ++j) {
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
