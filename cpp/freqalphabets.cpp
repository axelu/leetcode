
// 1309. Decrypt String from Alphabet to Integer Mapping
// https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/



class Solution {
public:
    string freqAlphabets(string s) {
        string r = "";

        auto it = s.rbegin();
        char ch;
        while(true) {
            if( *it == '#' ) {
                ch = 96 + ((*(it+2) - '0') * 10 + (*(it+1) - '0'));
                it += 3;
            } else {
                ch = 96 + (*(it) - '0');
                ++it;
            }
            r = ch + r;
            if( it == s.rend() ) break;
        }

        return r;
    }
};
