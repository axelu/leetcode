
// 3036. Number of Subarrays That Match a Pattern II
// https://leetcode.com/problems/number-of-subarrays-that-match-a-pattern-ii/

// same solution as // 3034. Number of Subarrays That Match a Pattern I
// at https://leetcode.com/problems/number-of-subarrays-that-match-a-pattern-i/



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
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        int n = nums.size();
        int m = pattern.size(); // 1 <= m == pattern.length < n

        // in pattern
        //    1 indicates nums[i] > nums[i-1]
        //    0 indicates nums[i] == nums[i]
        //   -1 indiactes nums[i] < nums[i-1]
        // let's translate nums into string S where
        //    S[0] == 'd'
        //    S[i] == 'a' if i > 0 and nums[i] > nums[i-1]
        //    S[i] == 'b' if i > 0 and nums[i] == nums[i]
        //    S[i] == 'c' if i > 0 and nums[i] < nums[i-1]
        // then we will tranlate out pattern into string W where
        //    W[i] == 'a' if pattern[i] == 1
        //    W[i] == 'b' if pattern[i] == 0
        //    W[i] == 'c' if pattern[i] == -1
        // then we can use a string match algorithm to find how often W occurs in S

        string S(n,'d');
        for(int i = 1; i < n; ++i)
            if( nums[i] > nums[i-1] )
                S[i] = 'a';
            else if( nums[i] == nums[i-1] )
                S[i] = 'b';
            else
                S[i] = 'c';

        string W(m,'a');
        for(int i = 0; i < m; ++i)
            if( pattern[i] == 0 )
                W[i] = 'b';
            else if( pattern[i] == -1 )
                W[i] = 'c';

        // Knuth Morris Pratt algorithm KMP
        int P[S.size()]; memset(P,0,sizeof P);
        int nP = kmp_search(S,W,P);

        return nP;
    }
};
