
// 212. Word Search II
// https://leetcode.com/problems/word-search-ii/






class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    Trie* root;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;
        for(int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    Trie* add(char c, Trie* dic) {
        struct Trie* tn = dic;

        int idx = c - 'a';
        if( !tn->children[idx] )
            tn->children[idx] = init();
        tn = tn->children[idx];
        // last node is end of word
        tn->endOfWord = true;
        return tn;
    }

    bool search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.length(); i++) {
            int idx = s[i] == '#' ? 26 : s[i] - 'a';
            if( !tn->children[idx] )
                return false;

            tn = tn->children[idx];
        }

        return (tn != NULL && tn->endOfWord);
    }

    int letters[26];

    bool areAlllettersOfWordInGrid(string s) {
        for(char c : s)
            if( !letters[c-'a'] ) return false;
        return true;
    }

    int m,n;
    bool found;


    // directions right,down,left,up
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    void dfs(vector<vector<char>>& board, int i, int j, string& word, int idx, int seen[], Trie* root) {
        Trie* tn = add(board[i][j],root);
        if( board[i][j] != word[idx] ) return;
        if( idx == word.size()-1 ) {
            // we are done
            found = true;
            return;
        }
        int seenIdx = i*n+j;
        seen[seenIdx] = 1;

        int i_new,j_new;
        // explore in all four directions
        for(int k = 0; k < 4; ++k) {
            i_new = i + dirR[k];
            if( i_new < 0 || i_new == m ) continue;
            j_new = j + dirC[k];
            if( j_new < 0 || j_new == n ) continue;

            // is the new cell already part of the path?
            if( seen[i_new*n+j_new] ) continue;

            dfs(board,i_new,j_new,word,idx+1,seen,tn);
            if( found ) break;
        }
        // backtrack
        seen[seenIdx] = 0;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();    // rows
        n = board[0].size(); // cols

        int i,j,k;
        memset(letters,0,sizeof letters);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                letters[board[i][j]-'a'] = 1;


        root = init();
        int seen[m*n];memset(seen,0,sizeof seen);
        vector<string> ans;
        for(k = 0; k < words.size(); ++k) {

            if( search(words[k],root) ) {
                ans.push_back(words[k]);
                continue;
            }

            if( !areAlllettersOfWordInGrid(words[k]) ) continue;

            // each cell could be the starting point
            found = false;
            for(int i = 0; i < m; ++i) {
                for(int j = 0; j < n; ++j) {
                    dfs(board,i,j,words[k],0,seen,root);
                    if( found ) {
                        ans.push_back(words[k]);
                        break;
                    }
                }
                if( found ) break;
            }

        }

        return ans;
    }
};
