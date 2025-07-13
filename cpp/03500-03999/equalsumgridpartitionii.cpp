
// 3548. Equal Sum Grid Partition II
// https://leetcode.com/problems/equal-sum-grid-partition-ii/




// see 3546. Equal Sum Grid Partition I https://leetcode.com/problems/equal-sum-grid-partition-i/




class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        long long row_sum[100000];memset(row_sum, 0, sizeof row_sum);
        long long col_sum[100000];memset(col_sum, 0 ,sizeof col_sum);
        unordered_map<long long,vector<vector<int>>> um; // val, {{i1,j1},{i2,j2}...}
        for(int i = 0; i < m; ++i) {     // row
            for(int j = 0; j < n; ++j) { // col
                row_sum[i] += (long long)grid[i][j];
                col_sum[j] += (long long)grid[i][j];
                um[grid[i][j]].push_back({i,j});
            }
        }

        // split horizontally
        long long row_prefixSum[100001];
        row_prefixSum[0] = 0LL;
        for(int i = 1; i <= m; ++i)
            row_prefixSum[i] = row_prefixSum[i-1] + row_sum[i-1];
        for(int i = 1; i < m; ++i) {
            long long top = row_prefixSum[i];
            long long bottom = row_prefixSum[m] - row_prefixSum[i];
            if( top == bottom )
                return true;

            if( top > bottom ) {
                long long diff = top - bottom;
                // do we have an element in top of value diff?
                auto f = um.find(diff);
                if( f != um.end() ) {
                    for(auto it = f->second.begin(); it != f->second.end(); ++it) {
                        if( it->at(0) < i ) {
                            if( i == 1 ) {
                                // we are in row 0
                                if( n == 2 || it->at(1) == 0 || it->at(1) == n-1 )
                                    return true;
                            } else {
                                // even though we are not in row 0,
                                // we could still cut off cells if the grid
                                // has only one col
                                if( n == 1 ) {
                                    if( it->at(0) == 0 || it->at(0) == i-1 )
                                        return true;
                                } else {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            if( bottom > top ) {
                long long diff = bottom - top;
                // do we have an element in bottom of value diff?
                auto f = um.find(diff);
                if( f != um.end() ) {
                    for(auto it = f->second.begin(); it != f->second.end(); ++it) {
                        if( it->at(0) >= i ) {
                            if( i == m-1 ) {
                                // we are in the last row
                                if( n == 2 || it->at(1) == 0 || it->at(1) == n-1 )
                                    return true;
                            } else {
                                // even though we are not in the last row,
                                // we could still cut off cells if the grid
                                // only has one col
                                if( n == 1 ) {
                                    if( it->at(0) == i || it->at(0) == m-1 )
                                        return true;
                                } else {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }


        // split vertically
        long long col_prefixSum[100001];
        col_prefixSum[0] = 0LL;
        for(int j = 1; j <= n; ++j)
            col_prefixSum[j] = col_prefixSum[j-1] + col_sum[j-1];
        for(int j = 1; j < n; ++j) {
            long long left = col_prefixSum[j];
            long long right = col_prefixSum[n] - col_prefixSum[j];
            if( left == right )
                return true;

            if( left > right ) {
                long long diff = left - right;
                // do we hace an element in left of value diff?
                auto f = um.find(diff);
                if( f != um.end() ) {
                    for(auto it = f->second.begin(); it != f->second.end(); ++it) {
                        if( it->at(1) < j ) {
                            if( j == 1 ) {
                                // we are in col 0
                                if( m == 2 || it->at(0) == 0 || it->at(0) == m-1 )
                                    return true;
                            } else {
                                // even though we are not in col 0,
                                // we could still cut off cells if the grid
                                // has only one row
                                if( m == 1 ) {
                                    if( it->at(1) == 0 || it->at(1) == j-1 )
                                        return true;
                                } else {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            if( right > left ) {
                long long diff = right - left;
                // do we have an element in right of value diff?
                auto f = um.find(diff);
                if( f != um.end() ) {
                    for(auto it = f->second.begin(); it != f->second.end(); ++it) {
                        if( it->at(1) >= j ) {
                            if( j == n-1 ) {
                                // we are in the last col
                                if( m == 2 || it->at(0) == 0 || it->at(0) == m-1 )
                                    return true;
                            } else {
                                // even though we are not in the last column
                                // we could still cut off cells if the grid
                                // only has one row
                                if( m == 1 ) {
                                    if( it->at(1) == j || it->at(1) == n-1 )
                                        return true;
                                } else {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }

        return false;
    }
};
