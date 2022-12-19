
// 2309. Greatest English Letter in Upper and Lower Case
// https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/



class Solution {
public:
    string greatestLetter(string s) {
        vector<bool> lower(26,false);
        vector<bool> upper(26,false);
        for(char c: s)
            if( islower(c) )
                lower[c-'a'] = true;
            else
                upper[c-'A'] = true;

        for(int i = 25; i >= 0; --i)
            if( lower[i] && upper[i] )
                return string(1,i+'A');


        return "";
    }
};
