
// 472. Concatenated Words
// https://leetcode.com/problems/concatenated-words/





class Solution {
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

    void add(string& s) {
        struct Trie* tn = root;

        int n = s.size();
        for(int i = 0; i < n; ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = n;
    }

    bool dfs(string& s, int pos, int mem[]) {
        if( mem[pos] ) return false;
        mem[pos] = 1;

        struct Trie* tn = root;

        int n = s.size();
        for(int i = pos; i < n; ++i) {
            int idx = s[i] - 'a';
            if( !tn->children[idx] )
                return false;

            tn = tn->children[idx];
            if( tn->endOfWord ) {
                if( i == n-1 ) return pos == 0 ? false : true;
                if( dfs(s,i+1,mem) ) return true;
            }
        }
        return false;
    }


public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        root = init();
        int i,n = words.size();
        for(i = 0; i < n; ++i)
            add(words[i]);

        int mem[1000];
        vector<string> ans;
        for(i = 0; i < n; ++i) {
            if( words[i].size() == 1 ) continue;
            memset(mem,0,sizeof mem);
            if( dfs(words[i],0,mem) ) ans.push_back(words[i]);
        }

        return ans;
    }
};
