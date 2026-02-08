
// 3775. Reverse Words With Same Vowel Count
// https://leetcode.com/problems/reverse-words-with-same-vowel-count/

class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();

        string ans = "";
        int first_word_vowel_count = 0;
        bool first_word_seen = false;
        string word = "";
        int vowel_count = 0;
        for(int i = 0; i < n; ++i) {
            if( !first_word_seen ) {
                word.push_back(s[i]);
                if( s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ) {
                    ++first_word_vowel_count;
                } else if( s[i] == ' ' ) {
                    ans += word;
                    word = "";
                    first_word_seen = true;
                }
                continue;
            }

            if( s[i] == ' ' ) {
                if( vowel_count == first_word_vowel_count )
                    reverse(word.begin(), word.end());
                ans += word;
                ans.push_back(' ');

                word = "";
                vowel_count = 0;

            } else {
                word.push_back(s[i]);
                if( s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' )
                    ++vowel_count;
            }
        }
        if( !first_word_seen )
            return s;
        // finish up
        if( vowel_count == first_word_vowel_count )
            reverse(word.begin(), word.end());
        ans += word;

        return ans;
    }
};
