
// 3517. Smallest Palindromic Rearrangement I
// https://leetcode.com/problems/smallest-palindromic-rearrangement-i/




class Solution {
public:
    string smallestPalindrome(string s) {
        // s is a palindrome
        int n = s.size();
        if( n < 4 )
            return s;

        // if n is odd, we have 1 char with odd count
        // that char goes in the middle

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char chr: s)
            ++cnt[chr-'a'];

        int odd_chr = -1;
        int l = 0;
        int r = n-1;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i] % 2 )
                odd_chr = i;
            while( cnt[i] > 1 ) {
                s[l++] = i + 'a';
                s[r--] = i + 'a';
                cnt[i] -= 2;
            }
        }

        if( n % 2 )
            s[l] = odd_chr + 'a';

        return s;
    }
};
