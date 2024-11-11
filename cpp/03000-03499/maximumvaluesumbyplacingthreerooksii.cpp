
// 3257. Maximum Value Sum by Placing Three Rooks II
// https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-ii/







/* implementation based on hints
 * couldn't come up with a way to keep the space to remember for a DP solution small enough
 * hints:
 * Save the top 3 largest values in each row.
 * Select any row, and select any of the three values stored in it.
 * Get the top 4 values from all of the other 3 largest values of the other rows,
 *     which do not share the same column as the selected value.
 * Brute force the selection of 2 positions from the top 4 now.



 */
class Solution {
private:

    int findtop(vector<vector<int>> top3byrow[], int m, int forbidden_row1, int fobidden_col1, int forbidden_row2, int forbidden_col2 ) {
        int mx = INT_MIN;
        for(int i = 0; i < m; ++i) {
            if( i == forbidden_row1 || i == forbidden_row2 )
                continue;

            for(int j = 0; j < 3; ++j) {

                if( top3byrow[i][j][2] == fobidden_col1 || top3byrow[i][j][2] == forbidden_col2 )
                    continue;

                mx = max(mx, top3byrow[i][j][0]);
            }
        }
        return mx;
    }

public:
    long long maximumValueSum(vector<vector<int>>& board) {
        int m = board.size();    // rows
        int n = board[0].size(); // cols

        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[0] > b[0];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

        vector<vector<int>> top3byrow[m]; // value: {val, row, col}
        for(int i = 0; i < m; ++i) {

            for(int j = 0; j < n; ++j) {
                pq.push({board[i][j],i,j});
                if( pq.size() > 3 )
                    pq.pop();
            }

            while( !pq.empty() ) {
                top3byrow[i].push_back(pq.top());
                pq.pop();
            }
        }
        /*
        // debug
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < 3; ++j)
                cout << top3byrow[i][j][0] << "," << top3byrow[i][j][1] << "," << top3byrow[i][j][2] << " ";
            cout << endl;
        }
        */

        long long ans = LLONG_MIN;

        for(int i = 0; i < m; ++i) {
            // cout << "processing row i " << i << endl;
            for(int j = 0; j < 3; ++j) {
                long long val1 = top3byrow[i][j][0];
                int forbidden_column = top3byrow[i][j][2]; // forbidden column

                // cout << "selected " << val1 << "," << top3byrow[i][j][1] << "," << forbidden_column << endl;

                // gather the top 4 values from all of the other 3 largest values of the other rows,
                // which do not share the same column as the selected value.

                // note because of the fact that we only have the 3 top per row, by
                // collecting 4 we will always have those spread accross 2 rows and with that have a solution

                for(int row = 0; row < m; ++row) {
                    if( row == i )
                        continue;

                    for(int k = 0; k < 3; ++k) {
                        int top3col = top3byrow[row][k][2];
                        if( top3col == forbidden_column )
                            continue;
                        pq.push(top3byrow[row][k]);
                        if( pq.size() > 4 )
                            pq.pop();
                    }
                }
                // pq now contains now the top 4 values from all rows other than row i
                // and neither value is in the column nor in the row of the selected value

                vector<vector<int>> v;
                while( !pq.empty() ) {
                    v.push_back(pq.top());
                    pq.pop();
                }
                // in v smallest value in front
                /*
                cout << "top 4 other rows and cols" << endl;
                for(int k = 0; k < 4; ++k)
                    cout << v[k][0] << "," << v[k][1] << "," << v[k][2] << " ";
                cout << endl;
                */
                // edge case
                // we could still find ourselfs with the selected top4 all being in the same column
                // if so, we need to find the top value not in the selected col nor in the column of
                // the top 4
                // hence same column check

                int top40col = v[0][2];
                bool havemorethanonecol = false;
                for(int k = 1; k < 4; ++k)
                    if( v[k][2] != top40col )
                        havemorethanonecol = true;
                if( !havemorethanonecol ) {
                    long long val3 = v[3][0];

                    long long val2 = findtop(top3byrow, m, i, forbidden_column, v[3][1], top40col);

                    ans = max(ans, val1 + val2 + val3);


                    continue;
                }

                // 2 out of 4
                // 0 1 2 3
                // x x
                // x   x
                // x     x
                //   x x
                //   x   x
                //     x x

                for(int k = 0; k < 3; ++k) {
                    long long val2 = v[k][0];
                    int row2 = v[k][1];
                    int col2 = v[k][2];
                    for(int l = k+1; l < 4; ++l) {
                        long long val3 = v[l][0];
                        int row3 = v[l][1];
                        int col3 = v[l][2];

                        if( row2 == row3 || col2 == col3 )
                            continue;

                        ans = max(ans, val1 + val2 + val3);
                    }
                }
            }
        }

        return ans;
    }
};
