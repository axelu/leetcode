
// 140. Word Break II
// https://leetcode.com/problems/word-break-ii/



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

    bool search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return( tn != NULL && tn->endOfWord );
    }

    void wordBreak(string s, vector<int> dp[], Trie* dic) {
        auto n = s.size();
        for(int i = 1; i <= n; ++i) {
            for(int j = i - 1; j >= 0; --j) {
                int l = i - j;
                string sub = s.substr(j,l);
                if( !dp[j].empty() && search(sub,dic) ) {
                    dp[i].push_back(l);
                }
            }
        }
    }

    void rec(string& s, vector<int> dp[], int i, vector<string>& v, vector<string>& ans) {
        if( i == 0 ) {
            string t = "";
            for(int k = v.size()-1; k >= 0; --k)
                t += v[k] + ' ';
            t.pop_back();
            ans.push_back(t);
            return;
        }

        for(int k = 0; k < dp[i].size(); ++k) {
            v.push_back(s.substr(i-dp[i][k],dp[i][k]));
            rec(s,dp,i-dp[i][k],v,ans);
            // backtrack
            v.pop_back();
        }
    }


public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // init Trie
        Trie* dic = init();
        for(string& s : wordDict)
            add(s, dic);

        auto n = s.size();
        vector<int> * dp = new vector<int>[n + 1];
        dp[0] = {0}; // start

        wordBreak(s, dp, dic);

        vector<string> ans;
        vector<string> v;
        rec(s,dp,n,v,ans);

        return ans;
    }
};
