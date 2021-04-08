
// 557. Reverse Words in a String III
// https://leetcode.com/problems/reverse-words-in-a-string-iii/



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
        size_t n = s.size();
        // trim leading and trailing spaces if any
        while( n > 0 && s[0] == ' ' ) {
            s.erase(0,1);
            --n;
        }
        while( n > 0 && s[n-1] == ' ' ) {
            s.erase(n-1);
            --n;
        }
        if( n < 2 ) return s; // base case

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
