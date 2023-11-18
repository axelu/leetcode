
// 1392. Longest Happy Prefix
// https://leetcode.com/problems/longest-happy-prefix/





class Solution {
private:
    // Knuth–Morris–Pratt
    vector<int> lps_table1(string& pattern) {
        // LPS (longest proper prefix that is also a suffix)
        int m = pattern.size();
        vector<int> LPS(m);
        LPS[0] = 0;  // LPS value of the first element is always 0
        int len = 0; // length of previous longest proper prefix that is also a suffix
        int i = 1;
        while( i < m ) {
            if( pattern[i] == pattern[len] ) {
                len = len + 1;
                LPS[i] = len;
                i = i + 1;
            } else {
                if( len != 0 )
                    len = LPS[len - 1];
                else {
                    LPS[i] = 0;
                    i = i + 1;
                }
            }
        }
        return LPS;
    }

public:
    string longestPrefix(string& s) {
        int n = s.size();
        if( n == 1 )
            return "";

        vector<int> LPS = lps_table1(s);
        return s.substr(0,LPS[n-1]);

    }
};
