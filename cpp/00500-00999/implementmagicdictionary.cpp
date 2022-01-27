
// 676. Implement Magic Dictionary
// https://leetcode.com/problems/implement-magic-dictionary/



class MagicDictionary {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    Trie* root;

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
        struct Trie* tn = dic;

        int idx;
        for(; i < s.length(); i++) {
            idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return( tn != NULL && tn->endOfWord );
    }

    bool magicSearch(string& s, Trie* dic) {
        struct Trie* tn = dic;

        int idx;
        for(int i = 0; i < s.length(); i++) {
            idx = s[i] - 'a';

            for(int j = 0; j < 26; ++j) {
                if( j == idx ) continue;
                if( tn->children[j] ) {
                    if( search(s,i+1,tn->children[j]) ) return true;
                }
            }

            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return false;
        // return( tn != NULL && tn->endOfWord );
    }


public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        root = init();
    }

    void buildDict(vector<string> dictionary) {
        for(int i = 0; i < dictionary.size(); ++i)
            add(dictionary[i],root);
    }

    bool search(string searchWord) {
        return magicSearch(searchWord,root);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
