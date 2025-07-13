
// 3597. Partition String
// https://leetcode.com/problems/partition-string/



class Solution {
private:
    vector<string> ans;

    struct Trie {
        struct Trie* children[26];
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    int add(string& s, int i, Trie* dic) {
        struct Trie* tn = dic;

        int start = i;
        int s_sz = s.size();
        for(; i < s_sz; ++i) {
            int idx = s[i] - 'a';
            if( !tn->children[idx] ) {
                tn->children[idx] = init();
                int length = i - start + 1;
                ans.push_back(s.substr(start, length));
                ++i;
                break;
            }
            tn = tn->children[idx];
        }

        return i;
    }



public:
    vector<string> partitionString(string s) {
        int n = s.size();

        Trie * root = init();

        int i = 0;
        while( i < n )
            i = add(s, i, root);

        return ans;
    }
};
