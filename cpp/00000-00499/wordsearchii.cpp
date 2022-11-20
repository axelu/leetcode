
// 212. Word Search II
// https://leetcode.com/problems/word-search-ii/


class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
        int words;
        string s;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;
        tn->words = 0;
 
        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, Trie* tn) {

        for(int i = 0; i < s.size(); ++i) {
            ++tn->words;
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
        tn->s = s;
    }
    
    int m,n;    
    int seen[12][12];
    vector<string> ans;
     
    // directions right,down,left,up
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};
    
    int dfs(vector<vector<char>>& board, int i, int j, Trie* tn) {

        int idx = board[i][j] - 'a';
        Trie* tn_nxt = tn->children[idx];
        if( !tn_nxt )
            return 0;

        int ret = 0;

        if( tn_nxt->endOfWord ) {
            ans.push_back(tn_nxt->s);
            tn_nxt->endOfWord = false;
            ++ret;
        }

        if( tn_nxt->words == 0 )
            return ret;

        seen[i][j] = 1;

        for(int k = 0; k < 4; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;
            
            int j_new = j + dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            if( seen[i_new][j_new] )
                continue;

            int t = dfs(board,i_new,j_new,tn_nxt);
            tn_nxt->words -= t; 
            ret += t;
            if( tn_nxt->words == 0 )
                break;
        }
        // backtrack
        seen[i][j] = 0;
        return ret;
    }
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();    // rows
        n = board[0].size(); // cols
      
        Trie* root = init();

        for(auto& s: words)
            add(s,root);

        for(int k = 0; k < 26; ++k) {
            if( !root->children[k] )
                continue;

            for(int i = 0; i < m; ++i) {
                for(int j = 0; j < n; ++j) {
                    if( board[i][j]-'a' == k ) {
                        memset(seen,0,sizeof seen);
                        int t = dfs(board,i,j,root);
                        root->words -= t;
                        if( root->words == 0 )
                            break;
                    }
                }
            }
        }

        return ans;
    }
};
