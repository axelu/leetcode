
// 208. Implement Trie (Prefix Tree)
// https://leetcode.com/problems/implement-trie-prefix-tree/



class Trie {
private:
    struct Dictionary {
        struct Dictionary* children[26];
        bool endOfWord;
    };

    Dictionary* dic;

    struct Dictionary* init() {
        struct Dictionary* tn =  new Dictionary;

        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s) {
        struct Dictionary* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    bool find(string& s) {
        struct Dictionary* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return( tn != NULL && tn->endOfWord );
    }

    bool beginsWith(string& s) {
        struct Dictionary* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return tn != NULL;
    }
public:
    /** Initialize your data structure here. */
    Trie() {
        dic = init();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        add(word);
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        return find(word);
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return beginsWith(prefix);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
