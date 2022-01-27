
// 562. Longest Line of Consecutive One in Matrix
// https://leetcode.com/problems/longest-line-of-consecutive-one-in-matrix/




class Solution {
    int m,n;

    int longestLineRow(vector<vector<int>>& mat) {
        int ret = 0;
        int t;
        for(int i = 0; i < m; ++i) {
            t = 0;
            for(int j = n-1; j >= 0; --j)
                if( mat[i][j] == 1 ) {
                    ++t;
                } else {
                    ret = max(ret,t);
                    t = 0;
                }
        }
        ret = max(ret,t);
        return ret;
    }

    int longestLineCol(vector<vector<int>>& mat) {
        int ret = 0;
        int t;
        for(int j = 0; j < n; ++j) {
            t = 0;
            for(int i = m-1; i >= 0; --i)
                if( mat[i][j] == 1 ) {
                    ++t;
                } else {
                    ret = max(ret,t);
                    t = 0;
                }
        }
        ret = max(ret,t);
        return ret;
    }

public:
    int longestLine(vector<vector<int>>& mat) {
        m = mat.size();     // rows
        n = mat[0].size();  // cols

        // the best possible answer is max[m,n];
        // diagonal or anti-diagonal best possible answer is min[m,n]



        int h = 0;                          // horizontal max
        int t;                              // horizontal helper
        int v = 0;                          // vertical max
        int u[n];memset(u,0,sizeof u);      // vertical helper
        int d = 0;                          // diagonal (top left bottom right) max
        int g[n][2];memset(g,0,sizeof g);   // diagonal (top left bottom right) helper
        int a = 0;                          // anti-diagonal (top right bottom left) max
        int b[n][2];memset(b,0,sizeof b);   // anti-diagonal (top right bottom left) helper

        for(int i = 0; i < m; ++i) {
            t = 0;
            for(int j = 0; j < n; ++j)
                if( mat[i][j] == 1 ) {
                    // horizontal
                    ++t;
                    if( j == n-1 )
                       h = max(h,t);

                    // vertical
                    ++u[j];
                    if( i == m-1 )
                        v = max(v,u[j]);

                    // diagonal
                    if( i == 0 ) {          // row 0
                        g[j][0] = 1;
                    } else if( j == 0 ) {   // col 0
                        g[0][i%2] = 1;
                    } else {
                        g[j][i%2] = g[j-1][!(i%2)]+1;
                    }
                    if( i == m-1 || j == n-1 )
                        d = max(d,g[j][i%2]);

                    // anti-diagonal
                    if( i == 0 ) {          // row 0
                        b[j][0] = 1;
                    } else if( j == n-1 ) { // col n-1
                        b[j][i%2] = 1;
                    } else {
                        b[j][i%2] = b[j+1][!(i%2)]+1;
                    }
                    if( i == m-1 || j == 0 )
                        a = max(a,b[j][i%2]);

                } else {
                    // horizontal
                    h = max(h,t);
                    t = 0;

                    // vertical
                    v = max(v,u[j]);
                    u[j] = 0;

                    // diagonal
                    if( i > 0 && j > 0 )
                        d = max(d,g[j-1][!(i%2)]);
                    g[j][i%2] = 0;

                    // anti-diagonal
                    if( i > 0 && j < n-1 )
                        a = max(a,b[j+1][!(i%2)]);
                    b[j][i%2] = 0;

                }

        }

        /*
        cout << "horizontal    " << h << endl;
        cout << "vertical      " << v << endl;
        cout << "diagonal      " << d << endl;
        cout << "anti-diagonal " << a << endl;
        */

        return max({h,v,d,a});
    }
};
