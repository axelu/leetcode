
// 3213. Construct String with Minimum Cost
// https://leetcode.com/problems/construct-string-with-minimum-cost/






class Solution {
private:

    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    Trie* root;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = -1;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, Trie* dic, int cost) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        if( tn->endOfWord == -1 || tn->endOfWord > cost )
            tn->endOfWord = cost;
    }

    int mem[50000];

    int search(string& s, int pos, Trie* dic) {
        // cout << "search pos " << pos << endl;
        int n = s.size();
        if( pos == n )
            return 0;

        if( mem[pos] != -1 )
            return mem[pos];

        struct Trie* tn = dic; // root

        int ret = 500000001;
        for(int i = pos; i < n; ++i) {
            int idx = s[i] - 'a';
            if( !tn->children[idx] )
                break;

            if( tn->children[idx]->endOfWord != -1 ) {
                // cout << "  found eow pos " << pos << " i " << i << endl;
                ret = min(ret, tn->children[idx]->endOfWord + search(s, i+1, dic));
            }
            tn = tn->children[idx];
        }

        return mem[pos] = ret;
    }

public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        root = init();

        int words_sz = words.size(); // words.length == costs.length
        for(int i = 0; i < words_sz; ++i)
            add(words[i], root, costs[i]);
        memset(mem,-1,sizeof mem);
        int ans = search(target, 0, root);
        return ans < 500000001 ? ans : -1;
    }
};
