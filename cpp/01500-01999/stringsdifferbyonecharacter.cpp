
// 1554. Strings Differ by One Character
// https://leetcode.com/problems/strings-differ-by-one-character/



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

    bool search(string& s, int i, Trie* dic) {
        int n = s.size();
        if( i == n )
            return true;

        struct Trie* tn = dic;

        for (; i < n; i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return tn != NULL ? true : false;
    }

    bool skipSearch(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';

            for(int c = 0; c < 26; ++c) {
                if( c == idx || !tn->children[c] )
                    continue;

                if( search(s,i+1,tn->children[c]) )
                    return true;
            }

            tn = tn->children[idx];
        }

        return false;
    }

public:
    bool differByOne(vector<string>& dict) {
        Trie* root = init();
        for(string& s : dict)
            add(s,root);

        for(string& s : dict)
            if( skipSearch(s,root) )
                return true;

        return false;
    }
};
