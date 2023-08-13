
// 2743. Count Substrings Without Repeating Character
// https://leetcode.com/problems/count-substrings-without-repeating-character/



class Solution {
public:
    int numberOfSpecialSubstrings(string s) {
        int n = s.size();

        int ans = 0;

        int cnt[26];memset(cnt,0,sizeof cnt);

        int i = 0, l;
        for(int j = 0; j < n; ++j) {
            int c = s[j]-'a';

            ++cnt[c];
            if( cnt[c] == 2 ) {
                l = (j-1) - i + 1;
                ans += (l * (l+1)/2);

                while( cnt[c] == 2 ) {
                    --cnt[s[i]-'a'];
                    ++i;
                }
                // don't double count
                l = j-i;
                ans -= (l * (l+1)/2);
            }
        }
        // finish up
        l = (n-1) - i + 1;
        ans += (l * (l+1)/2);


        return ans;
    }
};
