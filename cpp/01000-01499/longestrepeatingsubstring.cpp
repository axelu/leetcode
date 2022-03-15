
// 1062. Longest Repeating Substring
// https://leetcode.com/problems/longest-repeating-substring/


class Solution {
private:
    struct Trie {
        Trie* children[26];
    };

    Trie* dic;
    int n;

    Trie*  init() {
        Trie* tn =  new Trie;
        for(int i = 0; i < 26; ++i)
            tn->children[i] = NULL;
        return tn;
    }

    int add(string& s, int i) {
        struct Trie* tn = dic;

        int ret = 0;
        for(; i < n; ++i) {
            int idx = s[i] - 'a';
            if( !tn->children[idx] )
                tn->children[idx] = init();
            else
                ++ret;
            tn = tn->children[idx];
        }
        return ret;
    }

public:
    int longestRepeatingSubstring(string s) {
        dic = init();
        n = s.size();

        int ans = 0;
        for(int i = n-1; i >= 0; --i)
            ans = max(ans,add(s,i));

        return ans;
    }
};
