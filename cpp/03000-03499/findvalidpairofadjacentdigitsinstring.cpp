
// 3438. Find Valid Pair of Adjacent Digits in String
// https://leetcode.com/problems/find-valid-pair-of-adjacent-digits-in-string/




class Solution {
public:
    string findValidPair(string s) {
        int n = s.size();

        int cnt[11];memset(cnt,0,sizeof cnt);
        for(char c: s)
            ++cnt[c-'0'];

        for(int i = 0; i < n-1; ++i)
            if( s[i] != s[i+1] && s[i]-'0' == cnt[s[i]-'0'] && s[i+1]-'0' == cnt[s[i+1]-'0'])
                return s.substr(i,2);

        return "";
    }
};
