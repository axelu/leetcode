
// 1400. Construct K Palindrome Strings
// https://leetcode.com/problems/construct-k-palindrome-strings/




class Solution {
public:
    bool canConstruct(string& s, int k) {
        int n = s.size();
        if( n < k )
            return false;

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char c: s)
            ++cnt[c-'a'];

        // all character counts need to divide evenly
        // if some counts are odd, as long as odd count <= k,
        // we can distribute them

        int odd_cnt = 0;
        for(int i = 0; i < 26; ++i)
            if( cnt[i] % 2 == 1 )
                ++odd_cnt;

        return odd_cnt <= k;
    }
};
