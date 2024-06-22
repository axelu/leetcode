
// 3136. Valid Word
// https://leetcode.com/problems/valid-word/


class Solution {
public:
    bool isValid(string word) {
        if( word.size() < 3 )
            return false;

        bool has_vowel     = false;
        bool has_consonant = false;

        for(char c: word) {
            if( isalpha(c) ) {
                if( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ) {
                    has_vowel = true;
                } else {
                    has_consonant = true;
                }

            } else if( !isdigit(c) ) {
                return false;
            }
        }

        return has_vowel && has_consonant;
    }
};
