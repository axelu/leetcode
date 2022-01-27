
// 2083. Substrings That Begin and End With the Same Letter
// https://leetcode.com/problems/substrings-that-begin-and-end-with-the-same-letter/



class Solution {
public:
    long long numberOfSubstrings(string s) {
        long long cnt[26];memset(cnt,0,sizeof cnt);
        long long ans_arr[26];memset(ans_arr,0,sizeof ans_arr);

        for(char c : s)
            ans_arr[c-'a'] = ans_arr[c-'a'] + ( 1 + cnt[c-'a']++);

        // accumulate
        long long ans = 0;
        for(int i = 0; i < 26; ++i)
            ans += ans_arr[i];

        return ans;
    }
};
