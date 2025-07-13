
// 3541. Find Most Frequent Vowel and Consonant
// https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/




class Solution {
public:
    int maxFreqSum(string s) {
        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char chr: s)
            ++cnt[chr-'a'];

        // 01234567890123456789012345
        // abcdefghijklmnopqrstuvwxyz
        int mx_vowel = 0;
        int mx_consonant = 0;
        for(int i = 0; i < 26; ++i) {
            //         0    4    8   14   20
            // vowels 'a', 'e', 'i', 'o', 'u'
            if( i == 0 || i == 4 || i == 8 || i == 14 || i == 20 )
                mx_vowel = max(mx_vowel, cnt[i]);
            else
                mx_consonant = max(mx_consonant, cnt[i]);
        }

        return mx_vowel + mx_consonant;
    }
};
