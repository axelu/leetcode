
// 52. N-Queens II
// https://leetcode.com/problems/n-queens-ii/





class Solution {
private:
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

    void play(int game[], int n, int x, int& ans) {
        // attempt to place queen at x,y -> game[x][y] = 1
        //     mark all cells our queen can reach

        for(int y = 0; y < n; ++y)
            if( game[x*n+y] == 0 ) {
                // cout << "row " << x << " col " << y << " placing queen " << endl;
                placeQueen(game,n,x,y);
                // printgame(game,n);
                if( x == n-1 ) ++ans;
                else play(game,n,x+1,ans);
                // backtrack
                removeQueen(game,n,x,y);
            }
    }

public:
    int totalNQueens(int n) {
        // 1 <= n <= 9
        if( n == 1 ) return 1;
        if( n == 2 ) return 0;
        if( n == 3 ) return 0;

        int ans = 0;
        int game[n*n];memset(game,0,sizeof game);

        play(game,n,0,ans);
        return ans;

    }
};
