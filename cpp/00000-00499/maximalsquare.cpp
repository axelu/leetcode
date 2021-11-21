
// 221. Maximal Square
// https://leetcode.com/problems/maximal-square/





class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        if( m == 1 || n == 1 ) {
            for(int i = 0; i < m; ++i)
                for(int j = 0; j < n; ++j)
                    if( matrix[i][j] == '1' )
                        return 1;
            return 0;
        }

        int rt[m][n]; // count of 1s to the right
        int cnt = 0;  // total number of 1s
        for(int i = 0; i < m; ++i) {
            for(int j = n-1; j >= 0; --j) {
                if( matrix[i][j] == '1' )
                    ++cnt;
                if( j == n-1 || matrix[i][j] == '0' )
                    rt[i][j] = 0;
                else {
                    if( matrix[i][j+1] == '0' )
                        rt[i][j] = 0;
                    else
                        rt[i][j] = rt[i][j+1] + 1;
                }
            }
        }
        if( cnt == 0 )
            return 0;
        if( cnt < 4 )
            return 1;
        if( cnt == m*n )
            return min(m,n)*min(m,n);

        int ans = 1;
        int t,r;
        for(int i = 0; i < m-1; ++i) {
            for(int j = 0; j < n-1; ++j) {
                // cout << "i " << i << " j " << j << endl;
                if( matrix[i][j] == '0' )
                    continue;

                // how far down could we go from here?
                t = min(m-1-i,rt[i][j]);
                // cout << "t " << t << endl;
                if( t+1 <= ans )
                    continue;

                // going down
                // cout << "going down " << endl;
                for(int k = 1; k <= t; ++k) {
                    r = i+k;
                    // cout << "r " << r << endl;
                    if( matrix[r][j] == '0' )
                        break;

                    if( rt[r][j] < t )
                        t = rt[r][j];

                    if( rt[r][j] >= k ) {
                        /*
                        if( k+1 > ans ) {
                            cout << "ans " << k+1 << " at i " << i << " j " << j << endl;
                        }
                        */
                        ans = max(ans,k+1);
                    } else  {
                        break;
                    }
                }

            }
        }


        return ans*ans;
    }
};
