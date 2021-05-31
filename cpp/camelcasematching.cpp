
// 1023. Camelcase Matching
// https://leetcode.com/problems/camelcase-matching/




class Solution {
private:
    struct Trie {
        struct Trie* children[52]; // abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;

        for (int i = 0; i < 52; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    Trie* root;

    void add(string& s, Trie* dic) {
        struct Trie* tn = dic;

        int idx;
        for(int i = 0; i < s.size(); ++i) {
            idx = s[i] >= 97 ? s[i]-'a' : s[i]-'A'+26;

            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    bool search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        int idx;
        int n = s.length();
        int i = 0;
        for (; i < n; i++) {
            idx = s[i] >= 97 ? s[i]-'a' : s[i]-'A'+26;
            if( !tn->children[idx] ) {
                if( isupper(s[i]) ) {
                    return false;
                }
                continue;
            }

            tn = tn->children[idx];
        }

        return( tn != NULL && tn->endOfWord );
    }



public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        root = init();
        add(pattern,root);

        int n = queries.size();
        vector<bool> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = search(queries[i],root);
        return ans;
    }
};
