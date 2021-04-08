
// Replace All ?'s to Avoid Consecutive Repeating Characters
// https://leetcode.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/


class Solution {
public:
    string modifyString(string s) {

        for(auto it = s.begin(); it != s.end(); ++it) {
            if( *it != '?' ) continue;

            char l;
            char r;

            l = ( it == s.begin() ) ? 'z' : *(it - 1);
            r = ( it == s.end() - 1 ) ? 'a' : *(it + 1);

            *it = getChar(l, r);
        }

        return s;
    }
private:
    char getChar(char l, char r) {
        if( r == '?' ) r = 'a';

        char c = 'o';
        while( c == l || c == r ) {
            int idx = rand() % 26;
            c = 'a' + idx;
        }

        return c;
    }
};
