
// 2452. Words Within Two Edits of Dictionary
// https://leetcode.com/problems/words-within-two-edits-of-dictionary/




class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;
        tn->endOfWord = false;
        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;
        return tn;
    }

    void add(string& s, Trie* dic) {
        struct Trie* tn = dic;
        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();
            tn = tn->children[idx];
        }
        // last node is end of word
        tn->endOfWord = true;
    }

    // DFS
    bool search(string& s, int i, Trie* tn, int k) {
        if( i == s.size() )
            return true;

        // we can make k substitutions

        for(int c = 0; c < 26; ++c) {
            if( tn->children[c] ) {
                int k_new = c == s[i]-'a' ? k : k-1;
                if( k_new >= 0 && search(s,i+1,tn->children[c],k_new) )
                    return true;
            }
        }

        return false;
    }

public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {

        Trie* root = init();
        for(string& s: dictionary)
            add(s,root);

        vector<string> ans;

        for(string& s: queries)
            if( search(s,0,root,2) )
                ans.push_back(s);

        return ans;
    }
};
