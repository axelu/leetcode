
// 1704. Determine if String Halves Are Alike
// https://leetcode.com/problems/determine-if-string-halves-are-alike/

class Solution {
private:
    bool isVowel(char ch) {
       if( ch == 'a' ||
           ch == 'e' ||
           ch == 'i' ||
           ch == 'o' ||
           ch == 'u' ||
           ch == 'A' ||
           ch == 'E' ||
           ch == 'I' ||
           ch == 'O' ||
           ch == 'U' ) return true;
        return false;
    }
public:
    bool halvesAreAlike(string s) {
        size_t n = s.size();
        int a = 0, b = 0;

        int i = 0;
        for(; i < n/2; ++i)
            if( isVowel(s[i]) ) ++a;
        for(; i < n; ++i)
            if( isVowel(s[i]) ) ++b;

        return a == b;
    }
};
