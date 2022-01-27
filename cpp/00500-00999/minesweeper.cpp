
// 529. Minesweeper
// https://leetcode.com/problems/minesweeper/




class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        // click position will only be an unrevealed square ('M' or 'E')
        // mine 'M' is revealed = game is over
        if( board[click[0]][click[1]] == 'M' ) {
            board[click[0]][click[1]] = 'X';
            return board;
        }

        int m = board.size();
        int n = board[0].size();
        // cout << "m " << m << " n " << n << endl;

        int seen[m*n];memset(seen,0,sizeof seen);

        // 8 directions, starting North, then clockwise
        int dirR[] = {-1,-1, 0, 1, 1, 1, 0,-1};
        int dirC[] = { 0, 1, 1, 1, 0,-1,-1,-1};

        // BFS
        queue<pair<int,int>> q;
        q.push({click[0],click[1]});
        seen[click[0]*n+click[1]] = 1;
        int i,j,i_new,j_new,c;
        while( !q.empty() ) {
            i = q.front().first;
            j = q.front().second;
            // cout << "i " << i << " j " << j << endl;
            q.pop();
            if( board[i][j] == 'B' ) continue;
            c = 0;                      // count of adjacent mines
            stack<pair<int,int>> stck;  // park adjacent coordinates
            // explore all 8 directions
            for(int k = 0; k < 8; ++k) {

                i_new = i+dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;

                j_new = j+dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                // cout << "i_new " << i_new << " j_new " << j_new << endl;

                if( seen[i_new*n+j_new] )
                    continue;

                if( board[i_new][j_new] == 'M' || board[i_new][j_new] == 'X' ) {
                    ++c;
                } else {
                    stck.push({i_new,j_new});
                }
            }
            if( c != 0 ) {
                board[i][j] = c+48;
            } else {
                board[i][j] = 'B';
                while( !stck.empty() ) {
                    i_new = stck.top().first;
                    j_new = stck.top().second;
                    stck.pop();
                    seen[i_new*n+j_new] = 1;
                    q.push({i_new,j_new});
                }
            }
        }
        return board;
    }
};
