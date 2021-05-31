
// 79. Word Search
// https://leetcode.com/problems/word-search/





class Solution {
private:
    int m,n;
    bool found;

    // directions right,down,left,up
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    void dfs(vector<vector<char>>& board, int i, int j, string& word, int idx, int seen[]) {
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

            dfs(board,i_new,j_new,word,idx+1,seen);
            if( found ) break;
        }
        // backtrack
        seen[seenIdx] = 0;
    }


public:
    bool exist(vector<vector<char>>& board, string& word) {
        m = board.size();    // rows
        n = board[0].size(); // cols

        found = false;
        int seen[m*n];
        // each cell could be the starting point
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                memset(seen,0,sizeof seen);
                dfs(board,i,j,word,0,seen);
                if( found ) break;
            }
            if( found ) break;
        }
        return found;
    }
};
