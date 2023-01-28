
// 2186. Minimum Number of Steps to Make Two Strings Anagram II
// https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/



class Solution {
public:
    int minSteps(string s, string t) {

        int cnt_s[26];memset(cnt_s,0,sizeof cnt_s);
        for(char c: s)
            ++cnt_s[c-'a'];

        int cnt_t[26];memset(cnt_t,0,sizeof cnt_t);
        for(char c: t)
            ++cnt_t[c-'a'];

        /*
        for(int i = 0; i < 26; ++i)
            cout << char(i+'a') << ":" << cnt_s[i] << " ";
        cout << endl;
        for(int i = 0; i < 26; ++i)
            cout << char(i+'a') << ":" << cnt_t[i] << " ";
        cout << endl;
        */

        int ans = 0;
        for(int i = 0; i < 26; ++i)
            ans += abs(cnt_s[i] - cnt_t[i]);

        return ans;
    }
};
