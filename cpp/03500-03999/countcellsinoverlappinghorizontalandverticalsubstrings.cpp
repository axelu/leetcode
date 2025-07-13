
// 3529. Count Cells in Overlapping Horizontal and Vertical Substrings
// https://leetcode.com/problems/count-cells-in-overlapping-horizontal-and-vertical-substrings/





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
        int T[100001]; kmp_table(W,T); // Partial Match

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
    int countCells(vector<vector<char>>& grid, string pattern) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        int pattern_sz = pattern.size();

        // string by columns  vertical substring
        // top to bottom, then next column top to bottom
        string sc;
        for(int j = 0; j < n; ++j)     // col
            for(int i = 0; i < m; ++i) // row
                sc.push_back(grid[i][j]);

        int Pc[100000]; memset(Pc,0,sizeof Pc);
        int nPc = kmp_search(sc,pattern,Pc);
        if( nPc == 0 )
            return 0;


        // string by rows  horizontal substring
        // left to right, then next row left to right
        string sr;
        for(int i = 0; i < m; ++i)     // row
            for(int j = 0; j < n; ++j) // col
                sr.push_back(grid[i][j]);

        int Pr[100000]; memset(Pr,0,sizeof Pr);
        int nPr = kmp_search(sr,pattern,Pr);
        if( nPr == 0 )
            return 0;


        // mark cells that are part of pattern vertically
        vector<vector<bool>> gridv(m,vector<bool>(n,false));
        int idx_pc = 0; // index in Pc
        int idx_sc = 0; // index in sc
        int mx_idx_sc = -1;
        for(int j = 0; j < n; ++j) {     // col
            for(int i = 0; i < m; ++i) { // row
                if( idx_pc < nPc && Pc[idx_pc] == idx_sc ) {
                    // pattern starts in sc
                    // pattern runs till including idx_sc + pattern_sz - 1
                    mx_idx_sc = idx_sc + pattern_sz - 1;
                    ++idx_pc;
                }
                if( idx_sc <= mx_idx_sc )
                    gridv[i][j] = true;

                ++idx_sc;
            }
        }

        // debug
        /*
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << gridv[i][j];
            }
            cout << endl;
        }
        */

        int ans = 0;

        int idx_pr = 0; // index in Pr
        int idx_sr = 0; // index in sr
        int mx_idx_sr = -1;
        for(int i = 0; i < m; ++i) {     // row
            for(int j = 0; j < n; ++j) { // col
                if( idx_pr < nPr && Pr[idx_pr] == idx_sr ) {
                    // pattern starts in sr
                    // pattern runs till including idx_sr + pattern_sz - 1
                    mx_idx_sr = idx_sr + pattern_sz - 1;
                    ++idx_pr;
                }
                if( idx_sr <= mx_idx_sr && gridv[i][j] )
                    ++ans;

                ++idx_sr;
            }
        }

        return ans;
    }
};
