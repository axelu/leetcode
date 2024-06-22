
// 3093. Longest Common Suffix Queries
// https://leetcode.com/problems/longest-common-suffix-queries/

class Solution {
    struct Trie {
        struct Trie* children[26];
        int idx;
    };
    
    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->idx = -1;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }
    
    Trie* dic;
    
    void add(string& s, int idx) {
        struct Trie* tn = dic;

        for(int i = s.size() - 1; i >= 0; --i) {
            int c = s[i] - 'a';
            if (!tn->children[c]) {
                tn->children[c] = init();
                tn->children[c]->idx = idx;
            }

            tn = tn->children[c];
        }

        return;
    }

    int search(string& s) {
        struct Trie* tn = dic;

        int idx = -1;
        
        for(int i = s.size() - 1; i >= 0; --i) {
            int c = s[i] - 'a';
            if( tn->children[c] )
                idx = tn->children[c]->idx;
            else
                break;

            tn = tn->children[c];
        }

        return idx;
    }

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        vector<int> v(wordsContainer.size());
        iota(v.begin(), v.end(), 0);  // 0, 1, 2, 3, ..., wordsContainer.size() - 1
        sort(v.begin(), v.end(), [&wordsContainer](int a, int b){
            if( wordsContainer[a].size() < wordsContainer[b].size() ) {
                return true;
            } else if( wordsContainer[a].size() == wordsContainer[b].size() ) {
                return a < b;
            }
            return false;
        });
        
        dic = init();
        
        for(int i = 0; i < wordsContainer.size(); ++i)
            add(wordsContainer[v[i]], v[i]);
        
        int q_sz = wordsQuery.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int t = search(wordsQuery[i]);
            ans[i] = t != -1 ? t : v[0];
        }
        
        return ans;
    }
};
