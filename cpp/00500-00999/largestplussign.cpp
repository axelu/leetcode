
// 764. Largest Plus Sign
// https://leetcode.com/problems/largest-plus-sign/
// day 9 Sep 2021 challenge
// https://leetcode.com/explore/featured/card/september-leetcoding-challenge-2021/637/week-2-september-8th-september-14th/3969/






class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        if( mines.size() == n*n )
            return 0;
        if( mines.size() == n*n-1 )
            return 1;

        // we will use 0 as clear, 1 as mine !!!
        int grid[n][n];memset(grid,0,sizeof grid);
        for(int i = 0; i < mines.size(); ++i)
            grid[mines[i][0]][mines[i][1]] = 1;

        /*
        // grid
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << !grid[i][j] << " ";
            }
            cout << endl;
        }
        */

        int lt[n][n];
        int rt[n][n];
        int up[n][n];
        int dn[n][n];

        int jr,id;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                // cout << "i " << i << " j " << j << " grid[i][j] " << grid[i][j] << endl;

                // left
                if( j == 0 || grid[i][j] == 1) {
                    lt[i][j] = 0;
                } else {
                    if( grid[i][j-1] == 1 )
                        lt[i][j] = 0;
                    else
                        lt[i][j] = lt[i][j-1] + 1;
                }

                // right
                jr = n-1-j;
                if( jr == n-1 || grid[i][jr] == 1) {
                    rt[i][jr] = 0;
                } else {
                    if( grid[i][jr+1] == 1 )
                        rt[i][jr] = 0;
                    else
                        rt[i][jr] = rt[i][jr+1] + 1;
                }

                // up
                if( i == 0 || grid[i][j] == 1) {
                    up[i][j] = 0;
                } else {
                    if( grid[i-1][j] == 1 )
                        up[i][j] = 0;
                    else
                        up[i][j] = up[i-1][j] + 1;
                }

                 // down
                id = n-1-i;
                if( id == n-1 || grid[id][j] == 1) {
                    dn[id][j] = 0;
                } else {
                    if( grid[id+1][j] == 1 )
                        dn[id][j] = 0;
                    else
                        dn[id][j] = dn[id+1][j] + 1;
                }

            }
        }



        /*
        cout << "left" << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                cout << lt[i][j] << " ";
            cout << endl;
        }
        cout << "right" << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                cout << rt[i][j] << " ";
            cout << endl;
        }
        cout << "up" << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                cout << up[i][j] << " ";
            cout << endl;
        }
        cout << "down" << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                cout << dn[i][j] << " ";
            cout << endl;
        }
      */

        int ans = 0;
        int t;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                t = min({lt[i][j],rt[i][j],up[i][j],dn[i][j]});
                ans = max(ans,t);
            }
        }



        return ans+1;
    }
};
