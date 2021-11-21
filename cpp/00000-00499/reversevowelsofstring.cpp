
// 345. Reverse Vowels of String
// https://leetcode.com/problems/reverse-vowels-of-a-string/


class Solution {
public:
    string reverseVowels(string& s) {
        // abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
        // vowels: aeiouAEIOU

        size_t n = s.size();
        if( n <=1 ) return s;

        int i = 0;
        int j = n-1;
        char t;
        while( i < j ) {
            // advance i to vowel
            if( s[i]!='a' && s[i]!='e' && s[i]!='i' && s[i]!='o' && s[i]!='u' &&
                s[i]!='A' && s[i]!='E' && s[i]!='I' && s[i]!='O' && s[i]!='U') {
                ++i;
                continue;
            }
            // advance j to a vowel
            if( s[j]!='a' && s[j]!='e' && s[j]!='i' && s[j]!='o' && s[j]!='u' &&
                s[j]!='A' && s[j]!='E' && s[j]!='I' && s[j]!='O' && s[j]!='U') {
                --j;
                continue;
            }
            t = s[i];
            s[i] = s[j];
            s[j] = t;
            ++i;
            --j;
        }
        return s;
    }
};
