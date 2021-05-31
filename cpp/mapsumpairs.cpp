
// 677. Map Sum Pairs
// https://leetcode.com/problems/map-sum-pairs/






class MapSum {
private:
    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = 0;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    Trie* root;

    void add(string& s, int val, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = val;
    }

    Trie* search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return nullptr;

            tn = tn->children[idx];
        }

        return tn != NULL ? tn : nullptr;
    }

    int dfs(Trie* dic) {
        struct Trie* tn = dic;
        int ans = tn->endOfWord;

        for (int i = 0; i < 26; i++) {
            if (!tn->children[i])
                continue;

            ans += dfs(tn->children[i]);
        }

        return ans;
    }


public:
    /** Initialize your data structure here. */
    MapSum() {
        root = init();
    }

    void insert(string key, int val) {
        add(key,val,root);
    }

    int sum(string prefix) {
        Trie* tn = search(prefix,root);
        if( tn == nullptr ) return 0;

        return dfs(tn);
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
