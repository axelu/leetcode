
// 2416. Sum of Prefix Scores of Strings
// https://leetcode.com/problems/sum-of-prefix-scores-of-strings/




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

    void add(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
            ++tn->endOfWord;
        }

        // last node is end of word
        // ++tn->endOfWord;
    }

    int search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        int ret = 0;

        for (int i = 0; i < s.length(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                break;

            tn = tn->children[idx];
            ret += tn->endOfWord;
        }

        return ret;
    }


public:
    vector<int> sumPrefixScores(vector<string>& words) {
        int n = words.size();
        vector<int> ans;

        Trie* root = init();
        for(auto& s: words)
            add(s,root);

        for(auto& s: words)
            ans.push_back(search(s,root));

        return ans;
    }
};
