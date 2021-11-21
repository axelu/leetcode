
// 266. Palindrome Permutation
// https://leetcode.com/problems/palindrome-permutation/
// day 1 January 2021 challenge premium question
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/579/week-1-january-1st-january-7th/3588/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        size_t n = s.size();

        int cnt[128]; memset(cnt,0,sizeof cnt);
        int odd = 0;
        for(int i = 0; i < n; ++i) {
            ++cnt[s[i]];
            odd += cnt[s[i]] % 2 == 1 ? 1 : -1;
        }

        if( (n % 2 == 0 && odd == 0) || (n % 2 == 1 && odd == 1) ) return true;
        return false;
    }
};
