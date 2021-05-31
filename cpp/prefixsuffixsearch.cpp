
// 745. Prefix and Suffix Search
// https://leetcode.com/problems/prefix-and-suffix-search/
// day 1 May 2021 challenge
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3728/





class WordFilter {
private:
    struct Trie {
        struct Trie* children[27];
        int i;
        bool endOfWord;
    };

    Trie* root;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;
        tn->i = -1;
        for(int i = 0; i < 27; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, int pos, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] == '#' ? 26 : s[i] - 'a';
            if( !tn->children[idx] )
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->i = pos;
        tn->endOfWord = true;
    }

    Trie* search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.length(); i++) {
            int idx = s[i] == '#' ? 26 : s[i] - 'a';
            if( !tn->children[idx] )
                return nullptr;

            tn = tn->children[idx];
        }

        return tn != NULL ? tn : nullptr;
    }

    int dfs(Trie* tn) {
        int ans = tn->i;
        for(int i = 0; i < 27; ++i) {
            if( tn->children[i] != NULL )
                ans = max(ans,dfs(tn->children[i]));
        }
        return ans;
    }


public:
    WordFilter(vector<string>& words) {
        root = init();

        int n,j;
        string t;
        for(int i = 0; i < words.size(); ++i) {
            t = '#' + words[i];
            n = words[i].size();
            for(j = n-1; j >= 0; --j) {
                t = words[i][j] + t;
                // cout << "adding " << t << endl;
                add(t,i,root);
            }
        }
    }

    int f(string prefix, string suffix) {
        string t = suffix + '#' + prefix;
        Trie* tn = search(t,root);
        if( tn == nullptr ) return -1;
        return dfs(tn);
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */
