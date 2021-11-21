
// 1347. Minimum Number of Steps to Make Two Strings Anagram
// https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/




class Solution {
public:
    int minSteps(string s, string t) {
        int scnt[26];memset(scnt,0,sizeof scnt);
        int tcnt[26];memset(tcnt,0,sizeof tcnt);
        int n = s.size(); // s.length == t.length
        int i;
        for(i = 0; i < n; ++i) {
            ++scnt[s[i]-'a'];
            ++tcnt[t[i]-'a'];
        }

        int ans = 0;
        for(i = 0; i < 26; ++i)
            if( tcnt[i] < scnt[i] ) ans += (scnt[i]-tcnt[i]);

        return ans;
    }
};
