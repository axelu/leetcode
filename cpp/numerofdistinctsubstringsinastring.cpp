
// 1698. Number of Distinct Substrings in a String
// https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/




class Solution {
private:
    struct Trie {
        struct Trie* children[26];
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }


public:
    int countDistinct(string& s) {
        int n = s.size();
        if( n == 1 ) return 1;

        int ans = 0;

        /* TLE for C++
        // suffix trie
        Trie* root = init();
        Trie* tn;
        int j,idx;
        for(int i = 0; i < n; ++i) {
            // add(s,i,n,root);
            tn = root;
            for(j = i; j < n; ++j) {
                idx = s[j] - 'a';
                if (!tn->children[idx]) {
                    tn->children[idx] = init();
                    ++ans;
                }
                tn = tn->children[idx];
            }
        }
        return ans;*/

        // idea: Trie pre allocate memeory to avoid TLE
        // we can use a 2D array, where the columns are the 26 letters
        // the question is: how many layers do we need? n*n.
        int trie[250001][26];
        memset(trie,0,sizeof trie);
        int root,j;
        int * child;
        for(int i = 0; i < n; ++i) {
            root = 0; // we always start at row 0
            for(j = i; j < n; ++j) {
                child = &trie[root][s[j] - 'a'];
                if( !(*child) ) {
                    *child = ++ans; // we will point to a row that we could not have possibly been occupied before
                }
                root = *child;
            }
        }
        return ans;
    }
};
