





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
