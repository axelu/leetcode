
// 955. Delete Columns to Make Sorted II
// https://leetcode.com/problems/delete-columns-to-make-sorted-ii/





class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int m = strs.size();
        int n = strs[0].size();
        if( m == 1 )
            return 0;

        // cout << "m " << m << " n " << n << endl;

        // process till we find the 1st column j from the left
        // where each strs[i][j] >= strs[i-1][j] for 0 < i < m;
        int j = 0;
        int f;
        for(; j < n; ++j) {
            f = 2;  // 2 strs[i][j] > strs[i-1][j] for 0 < i < m
            for(int i = 1; i < m; ++i) {
                if( strs[i][j] < strs[i-1][j] ) {
                    f = 0;
                    break;
                } else if( strs[i][j] == strs[i-1][j] ) {
                    f = 1;
                }
            }
            if( f > 0 )
                break;
        }
        // cout << "j " << j << " f " << f << endl;
        if( j == n )
            return n;
        if( n == 1 && j == 0 )
            return 0;
        if( j == n-1 )
            return j;

        int t = j; // nbr of columns that have to be deleted so far
        // if we discover a column, in which strs[i][j] > strs[i-1][j] for 0 < i < m
        // then it does not matter what happens after
        if( f == 2 )
            return t;

        // we have at least two columns if we are here
        int grid[m][n];memset(grid,-1,sizeof grid);

        // process the 1st good column
        for(int i = 1; i < m; ++i) {
            if( strs[i][j] > strs[i-1][j] ) {
                grid[i][j] = 2;
            } else { // we know that strs[i][j] == strs[i-1][j]
                grid[i][j] = 1;
            }
        }
        // for(int i = 0; i < m; ++i)
        //    cout << i << ":" << grid[i][j] << endl;

        int last_j = j;
        ++j;

        // process the remaining columns
        for(; j < n; ++j) {
            f = 2;
            for(int i = 1; i < m; ++i) {
                if( strs[i][j] > strs[i-1][j] || grid[i][last_j] == 2 ) {
                    grid[i][j] = 2;
                } else {

                    if( strs[i][j] == strs[i-1][j] ) {
                        grid[i][j] = 1;
                        f = 1;
                    } else {
                        // we need to delete the column
                        f = 0;
                        break;
                    }
                }
            }
            if( f == 2 ) {
                // we are good for all remaining columns
                break;
            } else if( f == 0 ) {
                // cout << "deleting column j " << j << endl;
                ++t;
            } else {
                last_j = j;
            }
        }

        return t;
    }
};
