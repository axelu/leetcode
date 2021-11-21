
// 1858. Longest Word With All Prefixes
// https://leetcode.com/problems/longest-word-with-all-prefixes/





class Solution {
private:
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

    bool add(string& s, Trie* dic) {
        struct Trie* tn = dic;

        int n = s.size();
        bool f = true;
        for(int i = 0; i < n; ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx]) {
                tn->children[idx] = init();
            }

            tn = tn->children[idx];
            if( i < n-1 && !tn->endOfWord ) f = false;
        }

        // last node is end of word
        tn->endOfWord = true;
        return f;
    }

public:
    string longestWord(vector<string>& words) {
        sort(words.begin(),words.end(),[](const string& a, const string& b){
            if( a.size() < b.size() ) {
                return true;
            } else if( a.size() == b.size() ) {
                if( a < b ) return true;
            }
            return false;
        });

        string ans = "";
        int mx = 0;
        Trie* root = init();
        for(auto it = words.begin(); it != words.end(); ++it) {
            if( add(*it,root) ) {
                if( (*it).size() > mx ) {
                    mx = (*it).size();
                    ans = *it;
                }
            }
        }

        return ans;
    }
};
