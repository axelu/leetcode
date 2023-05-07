
// 2397. Maximum Rows Covered by Columns
// https://leetcode.com/problems/maximum-rows-covered-by-columns/



class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int m,n;
    int rows_skip;

    int rec(vector<vector<int>>& matrix, int numSelect, int s, int curr_column) {
        if( curr_column == n || countSetBits(s) == numSelect ) {
            int ret = 0;

            for(int i = 0; i < m; ++i) {
                if( (rows_skip >> i) & 1 )
                    continue;
                bool row_covered = true;
                for(int j = 0; j < n; ++j) {
                    if( matrix[i][j] && !((s >> j) & 1) ) {
                        row_covered = false;
                        break;
                    }
                }
                if( row_covered )
                    ++ret;
            }

            return ret;
        }

        // return the max number of rows we can cover based on the current column
        // and on the columns already selected thus far

        // at each column we have a choice
        //   don't add the current column to the set of columns selected
        //   add the column to the set of columns selected

        // don't add
        // if we don't add the current column and there is a row
        // that has a 1 in the current column, then this row cannot be covered
        // by any columns behind us
        int ret = rec(matrix,numSelect,s,curr_column+1);


        // add
        // if we add the current column but due to not selecting a prior column
        // a given row cannot be covered, then that row cannot be covered anymore
        s |= 1 << curr_column;
        return max(ret,rec(matrix,numSelect,s,curr_column+1));
    }


public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        m = matrix.size();      // rows
        n = matrix[0].size();   // cols

        // determine rows that can be skipped
        rows_skip = 0;
        int nbr_rows_skip = 0;
        for(int i = 0; i < m; ++i) {
            bool skip = true;
            for(int j = 0; j < n; ++j) {
                if( matrix[i][j] == 1 ) {
                    skip = false;
                    break;
                }
            }
            if( skip )
                rows_skip |= 1 << i;
        }
        // for(int i = 0; i < m; ++i)
        //    cout << i << ":" << ((rows_skip >> i) & 1) << " ";
        // cout << endl;

        if( countSetBits(rows_skip) == m )
            return m;


        return countSetBits(rows_skip) + rec(matrix,numSelect,0,0);
    }
};
