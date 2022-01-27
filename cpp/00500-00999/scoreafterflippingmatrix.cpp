
// 861. Score After Flipping Matrix
// https://leetcode.com/problems/score-after-flipping-matrix/



class Solution {
private:
    int m,n;

    void flipColumns(vector<vector<int>>& v) {
        int i,j,zeros;
        for(j = 1; j < n; ++j) {                // col
            zeros = 0;
            for(i = 0; i < m; ++i)              // row
                if( v[i][j] == 0 ) ++zeros;
            if( zeros > m/2 ) {
                // flip column
                for(i = 0; i < m; ++i)          // row
                    v[i][j] = v[i][j] == 0 ? 1 : 0;
            }
        }
    }

    int sum(vector<vector<int>>& v) {
        int f,t,s = 0;
        for(int i = 0; i < m; ++i) {
            f = 1;
            t = 0;
            for(int j = n-1; j >=0; --j) {
                t += v[i][j] * f;
                f *= 2;
            }
            s += t;
        }
        return s;
    }

public:
    int matrixScore(vector<vector<int>>& A) {
        m = A.size();    // rows
        n = A[0].size(); // cols

        // greedily we will need to get to where column 0 has all 1's
        // there are two ways of achieving this:
        // a) flip the rows that initially have a 0 in column 0
        // b) flip column 0 and then flip the rows that have a 0 in column 0
        // after either flip, we will only flip columns [1,n-1] in order to not
        // disturb column 0; we will flip a column, if the number of 0's is greater
        // then the number of 1s

        // TODO handle 1 column case

        int i,j;

        // approach a)
        vector<vector<int>> a(m,vector<int>(n));
        for(i = 0; i < m; ++i) {
            if( A[i][0] == 1 ) {
                for(j = 0; j < n; ++j)
                    a[i][j] = A[i][j];
            } else {
                // flip
                for(j = 0; j < n; ++j)
                    a[i][j] = A[i][j] == 0 ? 1 : 0;
            }
        }
        flipColumns(a);
        int suma = sum(a);

        // approach b)
        vector<vector<int>> b(m,vector<int>(n));
        for(i = 0; i < m; ++i)
            b[i][0] = A[i][0] == 0 ? 1 : 0;
        for(i = 0; i < m; ++i) {
            if( b[i][0] == 1 ) {
                for(j = 1; j < n; ++j)
                    b[i][j] = A[i][j];
            } else {
                // flip
                for(j = 1; j < n; ++j)
                    b[i][j] = A[i][j] == 0 ? 1 : 0;
            }
        }
        flipColumns(b);
        int sumb = sum(b);

        return max(suma,sumb);
    }
};
