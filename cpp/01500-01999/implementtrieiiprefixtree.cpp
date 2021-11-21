
// 1804. Implement Trie II (Prefix Tree)
// https://leetcode.com/problems/implement-trie-ii-prefix-tree/





class Trie {
private:
    struct trie {
        struct trie* children[26];
        int endOfWord;
    };

    struct trie* init() {
        struct trie* tn =  new trie;

        tn->endOfWord = 0;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    trie* root;

    void add(string& s, trie* dic) {
        struct trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        ++tn->endOfWord;
    }

    trie* search(string& s, trie* dic) {
        struct trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return nullptr;

            tn = tn->children[idx];
        }

        return tn != NULL ? tn : nullptr;
    }

    void del(string& s, trie* dic) {
        struct trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return;

            tn = tn->children[idx];
        }

        if( tn != NULL && tn->endOfWord > 0 )
            --tn->endOfWord;
    }

    int dfs(trie* dic) {
        struct trie* tn = dic;
        int ans = tn->endOfWord;

        for (int i = 0; i < 26; i++) {
            if (!tn->children[i])
                continue;

            ans += dfs(tn->children[i]);
        }

        return ans;
    }



public:
    Trie() {
       root = init();
    }

    void insert(string word) {
        add(word,root);
    }

    int countWordsEqualTo(string word) {
        trie* tn = search(word,root);
        return tn == nullptr ? 0 : tn->endOfWord;
    }

    int countWordsStartingWith(string prefix) {
        trie* tn = search(prefix,root);
        if( tn == nullptr ) return 0;

        return dfs(tn);
    }

    void erase(string word) {
        del(word,root);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */
