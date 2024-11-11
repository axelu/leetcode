
// 3240. Minimum Number of Flips to Make Binary Grid Palindromic II
// https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/





class Solution {
private:
    int count_ones(vector<vector<int>>& grid, int m, int n) {
        int ones = 0;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 )
                    ++ones;
        return ones;
    }

    int solve(vector<vector<int>>& grid, int m, int n) {
        int ret = 0;
        for(int rt = 0, rb = m-1; rt < rb; ++rt, --rb) {
            for(int cl = 0, cr = n-1; cl < cr; ++cl, --cr) {
                int ones = 0;
                ones += grid[rt][cl];
                ones += grid[rt][cr];
                ones += grid[rb][cl];
                ones += grid[rb][cr];
                if( ones == 1 || ones == 3 )
                    ret += 1;
                else if( ones == 2 )
                    ret += 2;
            }
        }
        return ret;
    }

    int mem_row[100001][2];

    int solve_row(vector<vector<int>>& grid, int m, int n, int j, int rem) {
        // remainder is either 0 or 2
        // we are going to represent remainder of 2 as 1

        int col_lft = j;
        int col_rgt = n-j-1;
        if( col_lft >= col_rgt ) {
            if( n % 2 ) {
                return solve_col(grid, m, n, 0, rem);
            } else {

                if( rem == 0 )
                    return 0;
                else
                    return 2;
            }
        }

        if( mem_row[j][rem] != -1 )
            return mem_row[j][rem];

        int mid_row = m / 2;

        // we have a choice
        //    don't flip grid[mid_row][col_lft] OR
        //    flip grid[mid_row][col_lft]

        int ret = INT_MAX;

        // don't flip
        if( grid[mid_row][col_lft] == 0 && grid[mid_row][col_rgt] == 0 )        // 0 0
            ret = min(ret, solve_row(grid, m, n, j+1, rem));
        else if( grid[mid_row][col_lft] == 0 && grid[mid_row][col_rgt] == 1 )   // 0 1
            ret = min(ret, 1 + solve_row(grid, m, n, j+1, rem)); // we are flipping grid[mid_row][col_rgt] to 0
        else if( grid[mid_row][col_lft] == 1 && grid[mid_row][col_rgt] == 0 )   // 1 0
            ret = min(ret, 1 + solve_row(grid, m, n, j+1, !rem)); // we are flipping grid[mid_row][col_rgt] to 1
        else                                                                    // 1 1
            ret = min(ret, solve_row(grid, m, n, j+1, !rem));

        // flip
        if( grid[mid_row][col_lft] == 0 && grid[mid_row][col_rgt] == 0 )        // 0 0
            ret = min(ret, 2 + solve_row(grid, m, n, j+1, !rem)); // we are flipping grid[mid_row][col_lft] to 1 grid[mid_row][col_rgt] to 1
        else if( grid[mid_row][col_lft] == 0 && grid[mid_row][col_rgt] == 1 )   // 0 1
            ret = min(ret, 1 + solve_row(grid, m, n, j+1, !rem)); // we are flipping grid[mid_row][col_lft] to 1
        else if( grid[mid_row][col_lft] == 1 && grid[mid_row][col_rgt] == 0 )   // 1 0
            ret = min(ret, 1 + solve_row(grid, m, n, j+1, rem)); // we are flipping grid[mid_row][col_lft] to 0
        else                                                                    // 1 1
            ret = min(ret, 2 + solve_row(grid, m, n, j+1, rem)); // we are flipping grid[mid_row][col_lft] to 0 grid[mid_row][col_rgt] to 0

        return mem_row[j][rem] = ret;
    }

    int mem_col[100001][2];

    int solve_col(vector<vector<int>>& grid, int m, int n, int i, int rem) {
        // remainder is either 0 or 2
        // we are going to represent remainder of 2 as 1

        int row_top = i;
        int row_btm = m-i-1;
        if( row_top >= row_btm ) {
            if( rem == 0 )
                return 0;
            else
                return 2;
        }

        if( mem_col[i][rem] != -1 )
            return mem_col[i][rem];


        int mid_col = n / 2;

        // we have a choice
        //    don't flip grid[row_top][mid_col] OR
        //    flip grid[row_top][mid_col]

        int ret = INT_MAX;

        // don't flip
        if( grid[row_top][mid_col] == 0 && grid[row_btm][mid_col] == 0 )        // t0 b0
            ret = min(ret, solve_col(grid, m, n, i+1, rem));
        else if( grid[row_top][mid_col] == 0 && grid[row_btm][mid_col] == 1 )   // t0 b1
            ret = min(ret, 1 + solve_col(grid, m, n, i+1, rem)); // we are flipping grid[row_btm][mid_col] to 0
        else if( grid[row_top][mid_col] == 1 && grid[row_btm][mid_col] == 0 )   // t1 b0
            ret = min(ret, 1 + solve_col(grid, m, n, i+1, !rem)); // we are flipping grid[row_btm][mid_col] to 1
        else                                                                    // t1 b1
            ret = min(ret, solve_col(grid, m, n, i+1, !rem));

        // flip
        if( grid[row_top][mid_col] == 0 && grid[row_btm][mid_col] == 0 )        // t0 b0
            ret = min(ret, 2 + solve_col(grid, m, n, i+1, !rem)); // we are flipping grid[row_top][mid_col] to 1 grid[row_btm][mid_col] to 1
        else if( grid[row_top][mid_col] == 0 && grid[row_btm][mid_col] == 1 )   // t0 b1
            ret = min(ret, 1 + solve_col(grid, m, n, i+1, !rem)); // we are flipping grid[row_top][mid_col] to 1
        else if( grid[row_top][mid_col] == 1 && grid[row_btm][mid_col] == 0 )   // t1 b0
            ret = min(ret, 1 + solve_col(grid, m, n, i+1, rem)); // we are flipping grid[row_top][mid_col] to 0
        else                                                                    // t1 b1
            ret = min(ret, 2 + solve_col(grid, m, n, i+1, rem)); // we are flipping grid[row_top][mid_col] to 0 grid[row_btm][mid_col] to 0

        return mem_col[i][rem] = ret;
    }

public:
    int minFlips(vector<vector<int>>& grid) {
        // minimum number of cells that need to be flipped to make
        // ALL rows AND columns palindromic, and total number of 1's in grid divisible by 4

        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        if( m * n < 4 ) {
            // only ans is 0 ones respectively all ones need to be flipped
            int ones = count_ones(grid, m, n);
            return ones;
        }

        if( m * n == 4 ) {
            int ones = count_ones(grid, m, n);
            if( ones == 0 || ones == 4 )
                return 0;
            else if( ones == 1 || ones == 3 )
                return 1;
            else
                return 2;
        }

        // as we need need to make rows AND cols palindromic, we will always end up with number ones divisible by 4,
        // we use greedy approach.
        // it boils down to the use having a middle row (odd number rows) and/or a middle col (odd number cols)
        // if we have both, odd number rows AND odd number cols, the center cell has to be 0

        int ans = solve(grid, m, n); // cout << "initial ans " << ans << endl;
        // number of ones at this point is always divisible by 4

        memset(mem_row, -1, sizeof mem_row);
        memset(mem_col, -1, sizeof mem_col);

        if( m % 2 == 1 && n % 2 == 0 ) {
            ans += solve_row(grid, m, n, 0, 0);

        } else if( m % 2 == 0 && n % 2 == 1 ) {
            ans += solve_col(grid, m, n, 0, 0);

        } else if( m % 2 == 1 && n % 2 == 1 ) {
            ans += solve_row(grid, m, n, 0, 0);

            int mid_row = m / 2;
            int mid_col = n / 2;
            ans += grid[mid_row][mid_col]; // center cell
        }

        return ans;
    }
};
