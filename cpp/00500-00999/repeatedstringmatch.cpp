
// 686. Repeated String Match
// https://leetcode.com/problems/repeated-string-match/






// https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm


class Solution {
private:
    vector<int> lps_table(string& pattern) {
        // LPS (longest proper prefix that is also a suffix)
        int m = pattern.size();
        vector<int> LPS(m);
        LPS[0] = 0;  // LPS value of the first element is always 0
        int k = 0; // length of previous longest proper prefix that is also a suffix
        for(int i = 1; i < m; ++i) {
            while( pattern[i] != pattern[k] && k > 0 )
                k = LPS[k-1];
            if( pattern[i] == pattern[k] )
                LPS[i]=++k;
        }
        return LPS;
    }

    int kmp_search(string& pattern, string& s) {
        // returns index of the 1st match of pattern in s or -1 if not found
        int n = s.size();
        int m = pattern.size();

        vector<int> LPS = lps_table(pattern);
        int j = 0; // index into pattern
        for(int i = 0; i < n; ++i) {
            while( pattern[j] != s[i] && j > 0)
                j = LPS[j-1];
            if( pattern[j] == s[i] ) {
                ++j;
                if( j == m )            // j pointer has reached end of pattern
                   return (i+1) - j;    // index of the match
            }
        }
        return -1;  // no match
    }

public:
    int repeatedStringMatch(string a, string b) {
        int a_sz = a.size(); // s is string
        int b_sz = b.size(); // b is pattern

        if( a_sz >= b_sz ) {
            int idx = kmp_search(b,a);
            if( idx > -1 )
                return 1;
            a = a + a;
            idx = kmp_search(b,a);
            if( idx > -1 )
                return 2;
            else
                return -1;
        } else {
            int r = 1;
            string s = a;
            while( a_sz < b_sz ) {
                ++r;
                a = a + s;
                a_sz = a.size();
            }
            int idx = kmp_search(b,a);
            if( idx > -1 )
                return r;
            ++r;
            a = a + s;
            idx = kmp_search(b,a);
            if( idx > -1 )
                return r;
            else
                return -1;
        }
    }
};
