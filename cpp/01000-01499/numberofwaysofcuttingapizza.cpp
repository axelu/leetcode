
// 1444. Number of Ways of Cutting a Pizza
// https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/




class Solution {
private:
    int m,n;
    long mod = 1000000007;
    long ps[51][51]; // 2D prefix sum
    long seen[51][51][11];

    long rec(int r, int c, int k) {
        // cout << "rec r " << r << " c " << c << " k " << k << endl;

        // r and c is the current upper left corner cell
        //     the next possible vertical cut is between column c and c+1
        //         but only if there is at least 1 apple in the left part
        //         and at least k-1 apples in the right part
        //     the next possible horizontal cut is between row r and r+1
        //         but only if there is at least 1 apple in the upper part
        //         and at least k-1 apples in the lower part

        if( seen[r][c][k] != -1 )
            return seen[r][c][k];

        long ret = 0;

        // horizontal cuts -> advance row
        // we can make the 1st cut when upper part has at least one apple
        int i = r;
        while( i < m-1 ) {
            // calculate number apples above our cut
            // rows above the cut r, r+1, r+2, ..., i
            int apples_above = ps[i+1][n] - ps[i+1][c] - ps[r][n] + ps[r][c];
            if( apples_above >= 1 )
                break;
            ++i;
        }
        // vertical cuts -> advance column
        // we can make the 1st cut when left part has at least one apple
        int j = c;
        while( j < n-1) {
            // calculate number apples left of our cut
            // columns left of our cut c, c+1, c+2, ..., ij
            int apples_left = ps[m][j+1] - ps[m][c] - ps[r][j+1] + ps[r][c];
            if( apples_left >= 1 )
                break;
            ++j;
        }

        if( k == 2 ) {
            // we have one more cut at our disposal

            // horizontal cuts
            while( i < m-1 ) {
                // we can make the cut if there is at least one apple below the cut
                // calculate number apples below our cut
                // rows below the cut i+1, i+2, ..., m-1
                int apples_below = ps[m][n] - ps[m][c] - ps[i+1][n] + ps[i+1][c];
                if( apples_below >= 1 )
                    ret = (ret + 1) % mod;
                else
                    break;
                ++i;
            }

            // vertical cuts
            while( j < n-1 ) {
                // we can make the cut if there is at least one apple right of the cut
                // calculate number apples right of our cut
                // columns right of the cut j+1, j+2, ..., n-1
                int apples_right = ps[m][n] - ps[m][j+1] - ps[r][n] + ps[r][j+1];
                if( apples_right >= 1 )
                    ret = (ret + 1) % mod;
                else
                    break;
                ++j;
            }

        } else {

            // horizontal cut
            while( i < m-1 ) {
                // we can make the cut if there are at least k-1 belows the cut
                // calculate number apples below our cut
                // rows below the cut i+1, i+2, ..., m-1
                int apples_below = ps[m][n] - ps[m][c] - ps[i+1][n] + ps[i+1][c];
                if( apples_below >= k-1 )
                    ret = (ret + rec(i+1,c,k-1)) % mod;
                else
                    break;
                ++i;
            }

            // vertical cut
            while( j < n-1 ) {
                // we can make the cut if there is at least one apple right of the cut
                // calculate number apples right of our cut
                // columns right of the cut j+1, j+2, ..., n-1
                int apples_right = ps[m][n] - ps[m][j+1] - ps[r][n] + ps[r][j+1];
                if( apples_right >= k-1 )
                    ret = (ret + rec(r,j+1,k-1)) % mod;
                else
                    break;
                ++j;
            }

        }

        return seen[r][c][k] = ret;
    }


public:
    int ways(vector<string>& pizza, int k) {
        // edge case
        if( k == 1 )
            return 1;

        m = pizza.size();
        n = pizza[0].size();

        // edge case
        if( m == 1 && n == 1 )
            return 1;

        // TODO potentially treat different if m == 1 OR n == 1
        //      then it becomes a 1d problem

        for(int i = 0; i <= m; ++i) {
            for(int j = 0; j <= n; ++j) {
                if( i == 0 || j == 0 ) {
                    ps[i][j] = 0;
                    continue;
                }
                int t = pizza[i-1][j-1] == 'A' ? 1 : 0;
                ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + t;
            }
        }

        /*
        // debug
        for(int i = 0; i <= m; ++i) {
            for(int j = 0; j <= n; ++j)
                cout << ps[i][j] << " ";
            cout << endl;
        }
        */

        memset(seen,-1,sizeof seen);
        return rec(0,0,k);
    }
};
