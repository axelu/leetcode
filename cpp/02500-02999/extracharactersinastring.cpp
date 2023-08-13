
// 2707. Extra Characters in a String
// https://leetcode.com/problems/extra-characters-in-a-string/



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

    vector<int> search(string& s, int i, Trie* dic) {
        struct Trie* tn = dic;

        vector<int> ret;

        for (; i < s.length(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                break;

            tn = tn->children[idx];
            if( tn->endOfWord )
                ret.push_back(i);
        }

        return ret;
    }

    int mem[50];

    int rec(string& s, int pos, Trie* dic) {
        int n = s.size();
        if( pos == n )
            return 0;

        if( mem[pos] != -1 )
            return mem[pos];

        int ret = n - pos; // worst case

        // we have a choice
        //    start from the current position in s OR
        //    skip the current char
        for(int i = pos; i < n; ++i) {
            int skipped = i - pos;
            vector<int> t = search(s,i,dic);
            for(int k = 0; k < t.size(); ++k) {
                // dictionary has a word that covers [i,t[k]] inclusive
                ret = min(ret, rec(s,t[k]+1,dic) + skipped);
            }
        }

        return mem[pos] = ret;
    }

public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();

        Trie* root = init();
        for(string s : dictionary)
            add(s,root);

        memset(mem,-1,sizeof mem);

        return rec(s,0,root);
    }
};
