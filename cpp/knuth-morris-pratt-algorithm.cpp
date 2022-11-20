

class Solution {
private:
    void kmp_table(string& W, int T[]) {
        // https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

        // input:  an array of characters, W (the word to be analyzed)
        // output: an array of integers, T (the table to be filled)

        int pos = 1; // current position we are computing in t
        int cnd = 0; // zero-based index in w of the next character of the current candidate substring

        T[0] = -1;

        while(pos < W.size()) {
            if( W[pos] == W[cnd] ) {
                T[pos] = T[cnd];
            } else {
                T[pos] = cnd;
                while(cnd >= 0 && W[pos] != W[cnd]) {
                    cnd = T[cnd];
                }
            }
            ++pos;
            ++cnd;
        }

        T[pos] = cnd; // only needed when all word occurrences are searched
    }

    int kmp_search(string& S, string& W, int P[]) {
        // https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

        // input:   an array of characters, S (the text to be searched)
        //          an array of characters, W (the word sought)
        // output:  an array of integers, P (positions in S at which W is found)
        //          an integer, nP (number of positions)

        int j = 0; // the position of the current character in S
        int k = 0; // the position of the current character in W
        int T[W.size()+1]; kmp_table(W,T); // Partial Match

        int nP = 0;

        while(j < S.size()) {
            if( W[k] == S[j] ) {
                ++j;
                ++k;
                if( k == W.size() ) {
                    // occurrence found, if only first occurrence is needed, m ← j - k  may be returned here
                    P[nP] = j - k; nP = nP + 1;
                    k = T[k]; // T[length(W)] can't be -1
                }
            } else {
                k = T[k];
                if( k < 0 ) {
                    ++j;
                    ++k;
                }
            }
        }
        return nP;
    }
public:
    bool isValid(string& s) {
        int n = s.size();
        if( n < 3 ) return false;
        if( n == 3 ) return s == "abc";


        string S = "ABC ABCDAB ABCDABCDABDE";
        string W = "ABCDABD";
        int P[S.size()]; memset(P,0,sizeof P);
        int nP = kmp_search(S,W,P);
        cout << nP << endl;
        for(int i = 0; i < S.size(); ++i)
            cout << P[i] << " ";
        cout << endl;



        return false;
    }
};


// ALTERNATIVE IMPLEMENTATION ( 2 different versions )
// https://www.scaler.com/topics/data-structures/kmp-algorithm/

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

// how to use the LPS table:
// If there is a match, increment both i and j.
// If there is a mismatch after a match, place j at LPS[pattern[j - 1]] and compare again.
// If j = 0, and there is a mismatch, increment i.

int kmp_search1(string& pattern, string& s) {
    // returns index of the 1st match of pattern in s or -1 if not found
    int n = s.size();
    int m = pattern.size();

    vector<int> LPS = lps_table1(pattern);
    int i = 0;
    int j = 0;
    while( i < n ) {
        if( pattern[j] == s[i] ) {
            i = i + 1;
            j = j + 1;
            if( j == m )        // j pointer has reached end of pattern
                return i - j;   // index of the match

        } else if( pattern[j] != s[i] && i < n ) {
            if( j > 0 )
                j = LPS[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;  // no match
}

vector<int> lps_table2(string& pattern) {
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

int kmp_search2(string& pattern, string& s) {
    // returns index of the 1st match of pattern in s or -1 if not found
    int n = s.size();
    int m = pattern.size();

    vector<int> LPS = lps_table1(pattern);
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

