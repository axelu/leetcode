
// 3006. Find Beautiful Indices in the Given Array I
// https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-i/



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

    // binary search lower boung
    int search(int nums[], int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

public:
    vector<int> beautifulIndices(string& s, string& a, string& b, int k) {
        int s_sz = s.size();
        // get the indicies at which a occurs in s
        // if a does not occur in s, return empty response
        int a_indicies[s_sz]; memset(a_indicies,0,sizeof a_indicies);
        int a_indicies_sz = kmp_search(s,a,a_indicies);
        if( a_indicies_sz == 0 )
            return {};

        // get the indicies at which b occurs in s
        // if b does not occur in s, return empty response
        int b_indicies[s_sz]; memset(b_indicies,0,sizeof b_indicies);
        int b_indicies_sz = kmp_search(s,b,b_indicies);
        if( b_indicies_sz == 0 )
            return {};

        vector<int> ans;

        // for every index i at which a occurs in s, determine
        // if there is an index j where b occurs in s and |j - i| <= k
        for(int a_indicies_idx = 0; a_indicies_idx < a_indicies_sz; ++a_indicies_idx) {
            int i = a_indicies[a_indicies_idx]; // i is an index at which a occurs in s
            int target = max(0, i - k);
            int b_indicies_idx = search(b_indicies,b_indicies_sz,target);
            if( b_indicies_idx == b_indicies_sz )
                continue;
            int j = b_indicies[b_indicies_idx];
            if( abs(i-j) <= k )
                ans.push_back(i);
        }

        return ans;
    }
};
