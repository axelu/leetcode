
// Check If a Word Occurs As a Prefix of Any Word in a Sentence
// https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/


class Solution {
public:
    int isPrefixOfWord(string& sentence, string& searchWord) {
        auto n = sentence.size();
        auto m = searchWord.size();
        // base cases
        if( n < m ) return -1;
        if( n == m ) return sentence == searchWord ? 1 : -1;

        int r = -1;

        // solution that avoids using extra storage

        int i = 0; // idx in sentence
        int j = 0; // idx in searchWord
        bool word = true;
        int wordidx = 1;
        for(; i < n; ++i) {
            if( word ) {
                if( sentence[i] == searchWord[j] ) {
                    if( j == m - 1 ) {
                        r = wordidx;
                        break;
                    }
                    ++j;
                } else {
                    word = false;
                }
            }
            if( !word ) {
                if( n - i < m ) break;
                if( sentence[i] == ' ' ) {
                    j = 0;
                    word = true;
                    ++wordidx;
                }
            }
        }

        return r;
    }
};
