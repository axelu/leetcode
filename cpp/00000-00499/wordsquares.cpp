
// 425. Word Squares
// https://leetcode.com/problems/word-squares/





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

    Trie* root;
    int m;
    vector<vector<string>> ans;

    void add(string& s) {
        struct Trie* tn = root;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }


    Trie* search(string& s) {
        struct Trie* tn = root;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return nullptr;

            tn = tn->children[idx];
        }

        return tn != NULL ? tn : nullptr;
    }



    void dfs(vector<string>& path, int depth) {
        if( depth == m ) {
            ans.push_back(path);
            return;
        }


        string prefix = "";
        for(int i = 0; i < path.size(); ++i)
            prefix += path[i][depth];

        Trie* tn = search(prefix);
        if( tn == nullptr ) return;

        dfs2(tn,prefix,path,depth);

    }

    void dfs2(Trie* dic, string& key, vector<string>& path, int depth) {
        struct Trie* tn = dic;

        for (int i = 0; i < 26; i++) {
            if (!tn->children[i])
                continue;

            key += 'a' + i;
            if( tn->children[i]->endOfWord ) {
                path.push_back(key);
                dfs(path,depth+1);
                path.pop_back();
            } else {
                dfs2(tn->children[i],key,path,depth);
            }
            key.pop_back();
        }

    }





public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        root = init();
        int n = words.size();
        m = words[0].size(); // All words[i] have the same length.
        int i;
        for(i = 0; i < n; ++i)
            add(words[i]);

        vector<string> path;
        for(i = 0; i < n; ++i) {
            path.push_back(words[i]);
            dfs(path,1);
            path.pop_back();
        }

        return ans;
    }
};
