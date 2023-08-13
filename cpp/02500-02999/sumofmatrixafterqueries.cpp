
// 2718. Sum of Matrix After Queries
// https://leetcode.com/problems/sum-of-matrix-after-queries/



class Solution {
public:
    long long matrixSumQueries(int n, vector<vector<int>>& queries) {
        // queries[i] = [typei, indexi, vali]

        vector<bool> seen_row(n,false);
        vector<bool> seen_col(n,false);

        int nbr_rows_seen = 0;
        int nbr_cols_seen = 0;

        long long ans = 0;

        int q_sz = queries.size();
        for(int k = q_sz-1; k >= 0; --k) {
            if( queries[k][0] == 0 ) {
                if( seen_row[queries[k][1]] )
                    continue;
                seen_row[queries[k][1]] = true;
                ++nbr_rows_seen;
                ans = ans + ((n - nbr_cols_seen) * queries[k][2]);

            } else {
                if( seen_col[queries[k][1]] )
                    continue;
                seen_col[queries[k][1]] = true;
                ++nbr_cols_seen;
                ans = ans + ((n - nbr_rows_seen) * queries[k][2]);
            }
        }

        return ans;
    }
};
