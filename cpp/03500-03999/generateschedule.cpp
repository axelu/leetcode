
// 3680. Generate Schedule
// https://leetcode.com/problems/generate-schedule/



class Solution {
private:
    int grid[50][50];
    int n, k_limit;

    // right of diagonal
    bool rec1(int i, int j, int k) {
        //string spacer(k,'|');
        //cout << spacer << "i " << i << " j " << j << " k " << k << endl;
        grid[i][j] = k;

        if( k == k_limit-1 )
            return true;

        // we can go from i,j to any cell i_new, j_new
        //     i_new and j_new are in bounds
        //     i_new != j_new
        //     i_new != i && j_new != j
        //     i_new and j_new are not i,j flip flopped

        for(int i_new = 0; i_new < n-1; ++i_new) {
            if( i_new == i || i_new == j )
                continue;

            for(int j_new = i_new+1; j_new < n; ++j_new) {
                if( j_new == j || j_new == i )
                    continue;

                if( i_new >= j_new ) // we are left of the diagonal
                    continue;

                if( grid[i_new][j_new] != -1 )
                    continue;

                if( rec1(i_new, j_new, k+1) )
                    return true;
            }
        }

        // backtrack
        grid[i][j] = -1;
        return false;
    }

    // left of diagonal
    bool rec2(int i, int j, int k) {
        //string spacer(k,'|');
        //cout << spacer << "i " << i << " j " << j << " k " << k << endl;
        grid[i][j] = k;

        if( k == k_limit-1 )
            return true;

        // we can go from i,j to any cell i_new, j_new
        //     i_new and j_new are in bounds
        //     i_new != j_new
        //     i_new != i && j_new != j
        //     i_new and j_new are not i,j flip flopped

        for(int i_new = 1; i_new < n; ++i_new) {
            if( i_new == i || i_new == j )
                continue;

            for(int j_new = 0; j_new < i_new; ++j_new) {
                if( j_new == j || j_new == i )
                    continue;

                if( j_new >= i_new ) // we are right of the diagonal
                    continue;

                if( grid[i_new][j_new] != -1 )
                    continue;

                if( rec2(i_new, j_new, k+1) )
                    return true;
            }
        }

        // backtrack
        grid[i][j] = -1;
        return false;
    }

public:
    vector<vector<int>> generateSchedule(int n) {
        // 2 <= n <= 50​​​​​​​

        // observation
        if( n <= 4 )
            return {};

        // pairs formula n * (n-1)/2
        // int pairs = n * ((n-1)/2); cout << "pairs " << pairs << endl;
        // we have 2 * pairs games

        memset(grid, -1, sizeof grid);
        this->n = n;
        int games = n * ((n-1)/2.0) * 2;
        k_limit = games / 2;

        // cout << "n " << n << " games " << games << " k_limit " << k_limit << endl;

        vector<vector<int>> ans(games);

        // right of diagonal
        bool f1 = rec1(0, 1, 0); // cout << f1 << endl;
        for(int i = 0; i < n; ++i)
            for(int j = i+1; j < n; ++j)
                ans[grid[i][j]] = {i,j};

        // left of diagonal

        // we have a solution for the 1st half of games
        // if ans[0] and ans[k_limt - 1] do not violate our constraint,
        // then we can just reverse i and j starting from k_limit
        // we know ans[0][0] = 0 and ans[0][1] = 1, as that is how we
        // started our recursion

        if( ans[k_limit-1][0] != 0 && ans[k_limit-1][1] != 0 &&
            ans[k_limit-1][0] != 1 && ans[k_limit-1][1] != 1 ) {

            for(int i = 0; i < k_limit; ++i)
                ans[i+k_limit] = {ans[i][1], ans[i][0]};

            return ans;
        }

        // we need to solve for the second half
        // the pairs in the first half i,j are all i < j
        // we need a starting pair a,b
        int a, b;
        bool f = false;
        for(a = 1; a < n; ++a) {
            if( a != ans[k_limit-1][0] && a != ans[k_limit-1][1] ) {
                for(b = 0; b < a; ++b) {
                    if( b != ans[k_limit-1][0] && b != ans[k_limit-1][1] ) {
                        f = true;
                        break;
                    }
                }
            }
            if( f )
                break;
        }

        // cout << "a " << a << " b " << b << endl;
        bool f2 = rec2(a, b, 0); // cout << f2 << endl;
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < i; ++j) {
                ans[grid[i][j] + k_limit] = {i,j};
            }

        return ans;
    }
};
