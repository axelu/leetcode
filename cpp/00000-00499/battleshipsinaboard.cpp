
// 419. Battleships in a Board
// https://leetcode.com/problems/battleships-in-a-board/




class Solution {
private:
    void explore(vector<vector<char>>& board, int m, int n, int i, int j, int seen[]) {
        seen[i*n+j] = 1;

        // down
        int i_new = i+1;
        if( i_new < m && board[i_new][j] == 'X' )
            explore(board,m,n,i_new,j,seen);

        // right
        int j_new = j+1;
        if( j_new < n && board[i][j_new] == 'X' )
            explore(board,m,n,i,j_new,seen);

    }
public:
    int countBattleships(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        int seen[m*n];memset(seen,0,sizeof seen);

        int ans = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( board[i][j] == 'X' && !seen[i*n+j] ) {
                    ++ans;
                    explore(board,m,n,i,j,seen);
                }
            }
        }
        return ans;
    }
};
