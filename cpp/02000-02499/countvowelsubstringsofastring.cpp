
// 2062. Count Vowel Substrings of a String
// https://leetcode.com/problems/count-vowel-substrings-of-a-string/



class Solution {
public:
    int countVowelSubstrings(string word) {
        // 01234567890123456789012345
        // abcdefghijklmnopqrstuvwxyz
        // vowels aeiou idx 0 4 8 14 20
        int n = word.size();

        int ans = 0, mask, c;
        for(int i = 0; i < n; ++i) {
            mask = 0;
            for(int j = i; j < n; ++j) {
                c = word[j]-'a';
                if( c != 0 && c != 4 && c != 8 && c != 14 && c != 20 )
                    break;

                mask |= 1 << c;
                if( mask == 1065233 )
                    ++ans;
            }
        }

        return ans;
    }
};
