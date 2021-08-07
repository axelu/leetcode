
// 151. Reverse Words in a String
// https://leetcode.com/problems/reverse-words-in-a-string/




class Solution {
private:
    void reverseString(string& s, int i, int j) {
        char t;
        while( i < j ) {
            if( s[i] != s[j] ) {
                t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
            ++i;
            --j;
        }
    }



public:
    string reverseWords(string& s) {
        int n = s.size();

        // trim leading spaces if any
        while( n > 0 && s[0] == ' ' ) {
            s.erase(0,1);
            --n;
        }
        // trim trailing spaces if any
        while( n > 0 && s[n-1] == ' ' ) {
            s.erase(n-1);
            --n;
        }
        // trim spaces between words if any
        bool hasSpace = false;
        for(int i = 0; i < n; ++i) {
            if( s[i] == ' ' ) {
                hasSpace = true;
                if( i+1 < n && s[i+1] == ' ' ) {
                    s.erase(i+1,1);
                    --n;
                    --i; // don't advance
                }
            }
        }

        // if there was no space, then there is only one word
        if( !hasSpace )
            return s;

        // reverse the entire string
        reverseString(s,0,n-1);

        // reverse words
        // https://leetcode.com/problems/reverse-words-in-a-string-iii/
        int lft = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == ' ' ) {
                if( i - lft > 1 ) reverseString(s,lft,i-1);
                lft = i+1;
            }
        }
        // finish up
        if( n - lft > 1 )
            reverseString(s,lft,n-1);


        return s;
    }
};
