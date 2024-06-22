
// 2132. Stamping the Grid
// https://leetcode.com/problems/stamping-the-grid/






class Solution {
private:
    int **bit; // 2D Binary Indexed Tree (Fenwick Tree) 1-indexed

    void add(int m, int n, int i, int j, int val) {
        for(++i; i < m; i += i & -i)
            for(int k = j+1; k < n; k += k & -k)
                bit[i][k] += val;
        return;
    }

    void range_add(int m, int n, int i1, int i2, int j1, int j2, int val) {
        add(m,n,i1,j1,val);
        add(m,n,i1,j2+1,-val);
        add(m,n,i2+1,j1,-val);
        add(m,n,i2+1,j2+1,val);
        return;
    }

    int point_query(int i, int j) {
        int ret = 0;
        for(++i; i > 0; i -= i & -i)
            for(int k = j+1; k > 0; k -= k & -k)
                ret += bit[i][k];
        return ret;
    }

public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int next[m][n]; // column index of next occupied cell to the right if current cell empty or
                        // current column index if cureent cell is occupied
        int cnt_empty = 0;
        for(int j = n-1; j >= 0; --j) {
            for(int i = 0; i < m; ++i) {
                if( grid[i][j] == 1 ) {
                    next[i][j] = j;
                } else {
                    ++cnt_empty;
                    next[i][j] = j == n-1 ? n : next[i][j+1];
                }
            }
        }

        if( cnt_empty == 0 )
            return true;
        if( stampHeight > m || stampWidth > n )
            return false;

        // init our 2D BIT
        bit = new int *[m+2];
        for(int i = 0; i <= m+1; i++) {
            bit[i] = new int[n+2];
            for(int j = 0; j <= n+1; ++j)
                bit[i][j] = 0;
        }

        map<int,int> mn[n];
        for(int j = 0; j <= n - stampWidth; ++j) {
            for(int i = 0; i <= m - stampHeight; ++i) {
                // we are trying to figure out if we can put our stamp's top left corner at grid[i][j]
                if( i == 0 ) {
                    // build the initial mn array
                    for(int k = 0; k < stampHeight; ++k)
                        ++mn[j][next[k][j]];
                } else {
                    --mn[j][next[i-1][j]];
                    if( mn[j][next[i-1][j]] == 0 )
                        mn[j].erase(next[i-1][j]);
                    ++mn[j][next[i+stampHeight-1][j]];
                }
                // t is min column index for rows[i,i+stampHeight-1] that has an occupied cell
                int t = mn[j].begin()->first;
                if( t - j >= stampWidth ) {
                    // we can place our stamp
                    // mark all cells covered by our stamp as stamped
                    range_add(m+1, n+1, i, i+stampHeight-1, j, j+stampWidth-1, 1);
                }
            }
        }

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 0 ) {
                    int t = point_query(i,j);
                    // cout << "i " << i << " j " << j << " stamped " << t << endl;
                    if( t == 0 ) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};
