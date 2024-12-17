
// 3359. Find Sorted Submatrices With Maximum Element at Most K
// https://leetcode.com/problems/find-sorted-submatrices-with-maximum-element-at-most-k/

// instead of using a full aux matrix, we could just have two arrays of length m
// and one is cur the other pre and just swap them on each iteration








class Solution {
public:
    long long countSubmatrices(vector<vector<int>>& grid, int k) {
        int n = grid.size();    // rows
        int m = grid[0].size(); // cols

        long long ans = 0;

        // we need an aux matrix where for each grid[i][j] we record
        // the longest increasing subarray of grid[i] ending at j
        vector<vector<int>> aux(n, vector<int>(m,0));

        // we empty the stack at each iteration aka after processing each column,
        // may as well define it here
        // monotonic increasing stack length,row
        stack<pair<int,int>> stck;

        // left to right, top to bottom
        for(int j = 0; j < m; ++j) {    // col
            // cout << "j " << j << endl;

            // adding sentinel to stack
            stck.push({0,-1});

            long long ans_col = 0LL;

            for(int i = 0; i < n; ++i) {
                // cout << "i " << i << endl;

                if( grid[i][j] > k ) {
                    aux[i][j] = 0;
                } else if( j > 0 ) {
                    if( grid[i][j-1] >= grid[i][j] ) {
                        aux[i][j] = aux[i][j-1] + 1;
                    } else {
                        aux[i][j] = 1;
                    }
                } else { // grid[i][j] <= k && j == 0
                   aux[i][j] = 1;
                }


                while( !stck.empty() && stck.top().first > aux[i][j] ) {
                    // we need to cash in

                    long long lgt = stck.top().first;
                    // long long row = stck.top().second;
                    stck.pop();

                    // we need to figure out what length diff to process
                    long long length_diff;
                    if( stck.top().first >  aux[i][j] )
                        length_diff = lgt - stck.top().first;
                    else
                        length_diff = lgt - aux[i][j];

                    // we need to figure out how many rows of that we have
                    long long rows = (i-1) - stck.top().second;

                    long long t = length_diff * ( rows * (rows + 1LL)/2LL );
                    // cout << "t " << t << endl;

                    ans_col = ans_col + t;
                }

                if( !stck.empty() && stck.top().first == aux[i][j] )
                    stck.pop();


                stck.push({aux[i][j], i});
            }

            // cout << "finishing column j " << j << endl;
            while( stck.size() > 1 ) {
                // we need to cash in
                // if we are processing the last aka smallest length, it goes all the way up
                // to the last time we saw a aux[j][i] == 0, or row 0;

                long long lgt = stck.top().first;
                // long long row = stck.top().second;;
                stck.pop();

                // we need to figure out what length diff to process
                long long length_diff = lgt -  stck.top().first;

                // we need to figure out how many rows of that we have
                long long rows = (n-1) - stck.top().second;

                long long t = length_diff * ( rows * (rows + 1LL)/2LL );

                ans_col = ans_col + t;

            }
            // remove sentinel or entry from last row where grid[i][j] > k
            stck.pop();

            ans = ans + ans_col;
            // debug
            // cout << "j " << j << " ans_col " << ans_col << " ans " << ans << endl;

        }

        // debug
        /*
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j)
                cout << aux[i][j] << " ";
            cout << endl;
        }
        */

        return ans;
    }
};
