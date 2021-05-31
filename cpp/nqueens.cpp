
// 51. N-Queens
// https://leetcode.com/problems/n-queens/
// day 22 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/601/week-4-may-22nd-may-28th/3752/



class Solution {
private:
    void printgame(int game[], int n) {
        int cnt = 0;
        for(int k = 0; k < n*n; ++k) {
            if( game[k] < 0 ) cout << game[k];
            else cout << " " << game[k];
            ++cnt;
            if( cnt == n ) {
                cnt = 0;
                cout << endl;
            }
        }
    }

    void game2board(int game[], int n, vector<vector<string>>& ans) {
        vector<string> board(n,string(n,'.'));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if( game[i*n+j] == -1) board[i][j] = 'Q';

        ans.push_back(board);
    }

    void placeQueen(int game[], int n, int x, int y) {
        // place queen
        game[x*n+y] = -1;

        int i,j;

        // mark south
        for(i = x+1; i < n; ++i)
            ++game[i*n+y];
        // mark south east
        for(i = x+1, j = y+1; i<n && j<n; ++i,++j)
            ++game[i*n+j];
        // mark south west
        for(i = x+1, j = y-1; i<n && j>=0; ++i,--j)
            ++game[i*n+j];
    }

    void removeQueen(int game[], int n, int x, int y) {
        // place queen
        game[x*n+y] = 0;

        int i,j;

        // mark south
        for(i = x+1; i < n; ++i)
            --game[i*n+y];
        // mark south east
        for(i = x+1, j = y+1; i<n && j<n; ++i,++j)
            --game[i*n+j];
        // mark south west
        for(i = x+1, j = y-1; i<n && j>=0; ++i,--j)
            --game[i*n+j];
    }

    void play(int game[], int n, int x, vector<vector<string>>& ans) {
        // attempt to place queen at x,y -> game[x][y] = 1
        //     mark all cells our queen can reach

        for(int y = 0; y < n; ++y)
            if( game[x*n+y] == 0 ) {
                // cout << "row " << x << " col " << y << " placing queen " << endl;
                placeQueen(game,n,x,y);
                // printgame(game,n);
                if( x == n-1 ) game2board(game,n,ans);
                else play(game,n,x+1,ans);
                // backtrack
                removeQueen(game,n,x,y);
            }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        // 1 <= n <= 9
        if( n == 1 ) return {{"Q"}};
        if( n == 2 ) return {};
        if( n == 3 ) return {};

        vector<vector<string>> ans;
        int game[n*n];memset(game,0,sizeof game);

        play(game,n,0,ans);
        return ans;
    }
};
