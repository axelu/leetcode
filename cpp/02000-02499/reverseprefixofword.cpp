
// 2000. Reverse Prefix of Word
// https://leetcode.com/problems/reverse-prefix-of-word/




class Solution {
public:
    string reversePrefix(string word, char ch) {
        auto e = word.find_first_of(ch);
        if( e == string::npos || e == 0 )
            return word;

        auto itb = word.begin();
        auto ite = word.begin();advance(ite,e+1);
        reverse(itb,ite);
        return word;
    }
};
