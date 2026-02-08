
// 3797. Count Routes to Climb a Rectangular Grid
// https://leetcode.com/problems/count-routes-to-climb-a-rectangular-grid/




class Solution {
private:
    const long mod = 1000000007;
    /*
    long mem[750][750][2];

    long rec(vector<string>& grid, int m, int n, int i, int j, bool samerow, int d2) {
        // cout << "rec i " << i << " j " << j << " samerow " << samerow << endl;
        if( i == 0 && samerow )
            return 1L;

        if( mem[i][j][samerow] != -1 )
            return mem[i][j][samerow];

        long ret = i == 0 ? 1L : 0L;

        if( i > 0 ) {
            // move up one row
            int i_new = i-1;
            for(int j_new = 0; j_new < n; ++j_new) {
                if( grid[i_new][j_new] == '#' )
                    continue;
                // Euclidean distance = sqrt( (r1 - r2)(r1 - r2) + (c1 - c2)(c1 - c2) )
                // Euclidean distance square = (r1 - r2)(r1 - r2) + (c1 - c2)(c1 - c2)
                //                             ------------------
                // Euclidean distance square =          1         + (c1 - c2)(c1 - c2)
                int ed2 = 1 + (j - j_new) * (j - j_new);
                if( ed2 > d2 )
                    continue;
                ret = (ret + rec(grid, m, n, i_new, j_new, false, d2)) % mod;
            }
        }
        if( !samerow ) {
            for(int j_new = 0; j_new < n; ++j_new) {
                if( j_new == j || grid[i][j_new] == '#' )
                    continue;
                // Euclidean distance = sqrt( (r1 - r2)(r1 - r2) + (c1 - c2)(c1 - c2) )
                // Euclidean distance square = (r1 - r2)(r1 - r2) + (c1 - c2)(c1 - c2)
                //                             ------------------
                // Euclidean distance square =          0         + (c1 - c2)(c1 - c2)
                int ed2 = (j - j_new) * (j - j_new);
                if( ed2 > d2 )
                    continue;
                ret = (ret + rec(grid, m, n, i, j_new, true, d2)) % mod;
            }
        }

        return mem[i][j][samerow] = ret;
    }
    */

public:
    int numberOfRoutes(vector<string>& grid, int d) {
        int m = grid.size(); // rows
        int n = grid[0].size(); // cols

        int d2 = d * d;


        long ans = 0;


        // top down memoization
        /*
        memset(mem,-1,sizeof mem);
        for(int j = 0; j < n; ++j) {
            if( grid[m-1][j] == '#' )
                continue;
            ans = (ans + rec(grid, m, n, m-1, j, false, d2)) % mod;
        }
        */


        // bottom up dp

        // for each j, let us calculate the min_j and max_j it can reach
        //    in the same row and
        //    in one row off
        // Euclidean distance = sqrt( (r1 - r2)(r1 - r2) + (c1 - c2)(c1 - c2) )
        // Euclidean distance square = (r1 - r2)(r1 - r2) + (c1 - c2)(c1 - c2)
        //                             ------------------
        // Euclidean distance square =          0         + (c1 - c2)(c1 - c2) same row
        // Euclidean distance square =          1         + (c1 - c2)(c1 - c2) next row

        // int samerowlimit_left[750];
        vector<int> samerowlimit_left(n);
        // int samerowlimit_right[750];
        vector<int> samerowlimit_right(n);
        // pair<int,int> nextrowlimit[750];
        vector<pair<int,int>> nextrowlimit(n);
        for(int j = 0; j < n; ++j) {
            // same row
            // left
            int j_min = 0;
            for(; j_min < j; ++j_min) {
                int ed2 = (j - j_min) * (j - j_min);
                if( ed2 <= d2 )
                    break;
            }
            samerowlimit_left[j] = j_min;
            // right
            int j_max = n-1;
            for(; j_max > j; --j_max) {
                int ed2 = (j - j_max) * (j - j_max);
                if( ed2 <= d2 )
                    break;
            }
            samerowlimit_right[j] = j_max;

            // next row
            nextrowlimit[j] = {-1,-1};
            j_min = 0;
            for(; j_min <= j; ++j_min) {
                int ed2 = 1 + (j - j_min) * (j - j_min);
                if( ed2 <= d2 )
                    break;
            }
            if( j_min <= j )
                nextrowlimit[j].first = j_min;
            j_max = n-1;
            for(; j_max >= j; --j_max) {
                int ed2 = 1 + (j - j_max) * (j - j_max);
                if( ed2 <= d2 )
                    break;
            }
            if( j_max >= j )
                nextrowlimit[j].second = j_max;
        }

        // row 0
        // same row true
        // long prefixSum_R0_samerow[751];
        // prefixSum_R0_samerow[0] = 0L;
        vector<long> prefixSum1(n+1);
        prefixSum1[0] = 0;
        for(int j = 1; j <= n; ++j) {
            // prefixSum_R0_samerow[j] = (prefixSum_R0_samerow[j-1] + (grid[0][j-1] == '.' ? 1 : 0)) % mod;
            prefixSum1[j] = (prefixSum1[j-1] + (grid[0][j-1] == '.' ? 1 : 0)) % mod;
        }
        // we are coming to row 0 from the row below
        // long prefixSum_R0_nextrow[751];
        // prefixSum_R0_nextrow[0] = 0L;
        vector<long> prefixSum2(n+1);
        prefixSum2[0] = 0;
        for(int j = 0; j < n; ++j) {
            long t = 0L;
            if( grid[0][j] == '.' ) {
                t = 1L; // we are in row 0
                // harvest left [j_min][j-1] same row
                // t = ((t + prefixSum_R0_samerow[j]) % mod) - prefixSum_R0_samerow[samerowlimit_left[j]];
                t = ((t + prefixSum1[j]) % mod) - prefixSum1[samerowlimit_left[j]];
                if( t < 0 )
                    t += mod;
                // harvest right [j+1][j_max] same row
                // t = ((t + prefixSum_R0_samerow[samerowlimit_right[j]+1]) % mod) - prefixSum_R0_samerow[j+1];
                t = ((t + prefixSum1[samerowlimit_right[j]+1]) % mod) - prefixSum1[j+1];
                if( t < 0 )
                    t += mod;
            }
            // prefixSum_R0_nextrow[j+1] = (prefixSum_R0_nextrow[j] + t) % mod;
            prefixSum2[j+1] = (prefixSum2[j] + t) % mod;
        }
        if( m == 1 )
            // return prefixSum_R0_nextrow[n];
            return prefixSum2[n];


        // long prefixSum1[751];
        // vector<long> prefixSum1(n+1);
        // long prefixSum2[751];
        // vector<long> prefixSum2(n+1);
        // prefixSum2[0] = 0;
        // for(int i = 1; i <= n; ++i)
        //     prefixSum2[i] = prefixSum_R0_nextrow[i];

        vector<long> row(n);

        for(int i = 1; i < m; ++i) {
            // built prefixSum for current row
            // pass1
            // harvest row above j_min, j_max
            prefixSum1[0] = 0;
            for(int j = 0; j < n; ++j) {
                long a = 0L;
                if( grid[i][j] == '.' ) {
                    // a = prefixSum_R0_nextrow[nextrowlimit[j].second+1] - prefixSum_R0_nextrow[nextrowlimit[j].first];
                    a = prefixSum2[nextrowlimit[j].second+1] - prefixSum2[nextrowlimit[j].first];
                    if( a < 0 )
                        a += mod;
                }
                prefixSum1[j+1] = (prefixSum1[j] + a) % mod;

                row[j] = a;
            }

            // pass 2 (built another prefixSum)
            // harvest same row left j_min, j-1
            // harvest same row right j_max, j+1
            prefixSum2[0] = 0;
            for(int j = 0; j < n; ++j) {
                long l = 0L;
                if( grid[i][j] == '.' ) {
                    l = prefixSum1[j] - prefixSum1[samerowlimit_left[j]];
                    if( l < 0 )
                        l += mod;
                }

                long r = 0L;
                if( grid[i][j] == '.' ) {
                    r = prefixSum1[samerowlimit_right[j]+1] - prefixSum1[j+1];
                    if( r < 0 )
                        r += mod;
                }

                prefixSum2[j+1] = (prefixSum2[j] + l + r + row[j]) % mod; // row[j] is what we carry
            }


            // TODO, but we actually don't need to do that
            // set our prefixSum to the prior prefix sum
            // swap(prefixSum1, prefixSum2);
        }

        // sum row m-1
        return prefixSum2[n];
    }
};
