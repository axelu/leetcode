
// 336. Palindrome Pairs
// https://leetcode.com/problems/palindrome-pairs/




class Solution {
private:
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

    void add(string& s, int pos, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = s.size()-1; i >= 0; --i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->idx = pos;
    }

    Trie* search(string& s, int pos, Trie* dic, vector<vector<int>>& ans) {
        struct Trie* tn = dic;

        int n = s.length();
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return nullptr;

            tn = tn->children[idx];
            if( tn->idx != -1 && validPalindrome(s,i+1) && pos != tn->idx )
                ans.push_back({pos,tn->idx});

        }

        return tn != NULL ? tn : nullptr;
    }

    void dfs(Trie* dic, string& s, int pos, vector<vector<int>>& ans) {

        struct Trie* tn = dic;

        for (int i = 0; i < 26; i++) {
            if (!tn->children[i])
                continue;

            s += i + 'a';
            if( tn->children[i]->idx != -1 && validPalindrome(s) && pos != tn->children[i]->idx )
                ans.push_back({pos,tn->children[i]->idx});
            dfs(tn->children[i],s,pos,ans);
            s.pop_back(); // backtracking
        }
    }

    bool validPalindrome(string& s) {
        return validPalindrome(s,0,s.size()-1);
    }

    bool validPalindrome(string& s, int l) {
        return validPalindrome(s,l,s.size()-1);
    }

    bool validPalindrome(string& s, int l, int r) {
        if( s.empty() ) return false;
        while(l<r) {
            if( s[l] != s[r] ) return false;
            ++l;
            --r;
        }
        return true;
    }

public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        Trie* root = init();

        vector<vector<int>> ans;

        int n = words.size(), i, empty = -1;
        int ps[n];memset(ps,0,sizeof ps);
        for(i = 0; i < n; ++i) {
            if( words[i].empty() )
                empty = i;
            if( validPalindrome(words[i]) )
                ps[i] = 1;
            add(words[i],i,root);
        }
        if( empty != -1 )
            for(i = 0; i < n; ++i)
                if( ps[i] ) {
                    ans.push_back({empty,i});
                    ans.push_back({i,empty});
                }


        string t = "";
        Trie* res;
        for(i = 0; i < n; ++i) {
            if( words[i].empty() ) continue;
            res = search(words[i],i,root,ans);
            if( res == nullptr )
                continue;

            dfs(res,t,i,ans);
        }

        return ans;
    }
};
