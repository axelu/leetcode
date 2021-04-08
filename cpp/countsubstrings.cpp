
// 1638. Count Substrings That Differ by One Character
// https://leetcode.com/problems/count-substrings-that-differ-by-one-character/



class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    Trie* dic;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = 0;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord += 1;
    }

    int search(string& s) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return tn != NULL ? tn->endOfWord : 0;
    }

public:
    int countSubstrings(string s, string t) {

        // init dictionary, etc.
        dic = init();
        auto m = t.size();
        unordered_set<char> uc; // unique chars in t
        string str;
        for(int i = 0; i < m; ++i) {
            uc.insert(t[i]);
            for(int j = i; j < m; ++j) {
                str = t.substr(i,j-i+1);
                add(str);
            }
        }

        int r = 0;
        auto n = s.size();
        auto itb = begin(uc);
        auto ite = end(uc);
        size_t k;
        string ss;
        for(int i = 0; i < n; ++i) {
            for(int j = i; j < n; ++j) {
                str = s.substr(i,j-i+1);

                k = str.size();
                for(auto it = itb; it != ite; ++it) {
                    for(int l = 0; l < k; ++l) {
                        if( *it == str[l] ) continue;
                        ss = str;
                        ss[l] = *it;
                        r += search(ss);
                    }
                }

            }
        }

        return r;
    }
};
