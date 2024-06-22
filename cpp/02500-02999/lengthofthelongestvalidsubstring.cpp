
// 2781. Length of the Longest Valid Substring
// https://leetcode.com/problems/length-of-the-longest-valid-substring/




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

    Trie* dic;

    void add(string& s) {
        struct Trie* tn = dic;

        // adding string backwards
        for(int i = s.size() - 1; i >= 0; --i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    bool search(string& s, int b, int e) {
        struct Trie* tn = dic;

        int i = e;
        for (; i >= b; --i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
            // exit if node is end of word
            if( tn->endOfWord )
                return true;
        }

        return (tn != NULL && tn->endOfWord);
    }

public:
    int longestValidSubstring(string& word, vector<string>& forbidden) {
        int n = word.size();

        // if a given forbidden word occurs one or more times in word, then
        // it obviously starts and ends at a given index
        // properties of a valid substring:
        // - cannot start AND end at indicies that a given forbidden word starts and ends
        // - cannot eclipse start AND end at indicies that a given forbidden word starts and ends at

        dic = init();

        for(string& s: forbidden)
            add(s);

        int ans = 0;

        // sliding window
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index
            // for the current window, we need to check if a forbidden string
            // ends at our right index, in which case we need to shrink our window
            while( i <= j && search(word,i,j) )
                ++i;
            ans = max(ans, j - i + 1);
        }

        return ans;
    }
};
