
// 3043. Find the Length of the Longest Common Prefix
// https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/




class Solution {
private:
    struct Trie {
        struct Trie* children[10];
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;

        for (int i = 0; i < 10; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - '0';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    int search(string s, Trie* dic) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - '0';
            if (!tn->children[idx])
                return i;

            tn = tn->children[idx];
        }

        return s.size();
    }

public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        int n1 = arr1.size();
        int n2 = arr2.size();

        // 1 <= arr1.length, arr2.length <= 5 * 1e4
        // worst case n1 = 50,000, n1 = 50,000 -> n1 * n2 pairs = 2,500,000,000

        Trie* root = init();
        for(int i : arr1)
            add(to_string(i),root);

        int ans = 0;

        for(int i : arr2)
            ans = max(ans, search(to_string(i),root));

        return ans;
    }
};
