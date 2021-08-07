
// 1945. Sum of Digits of String After Convert
// https://leetcode.com/problems/sum-of-digits-of-string-after-convert/
// https://leetcode.com/contest/weekly-contest-251/problems/sum-of-digits-of-string-after-convert/




class Solution {
public:
    int getLucky(string s, int k) {
        string t = "";
        for(int i = 0; i < s.size(); ++i)
            t += to_string(s[i]-'a'+1);

        int ans;

        for(int i = 0; i < k; ++i) {
            ans = 0;
            for(int j = 0; j < t.size(); ++j)
                ans += t[j]-'0';
            t = to_string(ans);
        }

        return ans;
    }
};
