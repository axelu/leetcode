
// 3742. Maximum Path Score in a Grid
// https://leetcode.com/problems/maximum-path-score-in-a-grid/

class Solution {
private:
    const int INF = 100000;

    int mincost[200][200];

    int rec_mincost(vector<vector<int>>& grid, int m, int n, int i, int j) {
        if( mincost[i][j] != -1 )
            return mincost[i][j];

        int local_cost = grid[i][j] != 0 ? 1 : 0;
        if( i == m-1 && j == n-1 )
            return mincost[i][j] = local_cost;

        int ret = INF;

        // go right
        int i_new = i;
        int j_new = j + 1;
        if( j_new < n )
            ret = local_cost + rec_mincost(grid, m, n, i_new, j_new);

        // go down
        i_new = i + 1;
        j_new = j;
        if( i_new < m )
            ret = min(ret, local_cost + rec_mincost(grid, m, n, i_new, j_new));

        return mincost[i][j] = ret;
    }

    // map<int,int> mem;
    // unordered_map<int,int> mem;
    vector<vector<vector<int>>> mem;

    int rec(vector<vector<int>>& grid, int m, int n, int i, int j, int k) {
        if( k < mincost[i][j] )
            return -1;

        // possible minor optimization
        //     regardless of k (as long as k >= mincost[i][j], which
        //     we already checked), if we are in the last row or last
        //     column, we can return the respective score

        int local_score = grid[i][j];
        if( i == m-1 && j == n-1 )
            return local_score;

        /*
        int key = (i<<18) + (j<<10) + k;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;
        */
        if( mem[i][j][k] != -1 )
            return mem[i][j][k];

        int local_cost = grid[i][j] != 0 ? 1 : 0;
        int ret = -1;

        // go right
        int i_new = i;
        int j_new = j + 1;
        if( j_new < n ) {
            int a = rec(grid, m, n, i_new, j_new, k - local_cost);
            if( a != -1 )
                ret = local_score + a;
        }

        // go down
        i_new = i + 1;
        j_new = j;
        if( i_new < m ) {
            int b = rec(grid, m, n, i_new, j_new, k - local_cost);
            if( b != -1 )
                ret = max(ret, local_score + b);
        }

        // return mem[key] = ret;
        return mem[i][j][k] = ret;
    }

public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        // 1 <= m, n <= 200
        // grid[0][0] == 0
        // 0 <= grid[i][j] <= 2

        // idea
        //     we could make a run and for each cell determine
        //     the minimum cost needed to reach (m-1, n-1)
        //     then when we get to a cell we can check quickly
        //     if it is even possible to reach (m-1, n-1)

        memset(mincost,-1,sizeof mincost);
        rec_mincost(grid, m, n, 0, 0);
        if( mincost[0][0] > k )
            return -1;
        // edge case
        if( k == 0 )
            return 0;

        mem = vector(m,vector(n,vector(k+1,-1)));
        return rec(grid, m, n, 0, 0, k);
    }
};

// passes 508/529 test cases, then TLE as of 11/10/2025
// case 509 runs in ~ 96ms with correct result, but obviously too slow
// then changed from map to unordered_map, which runs in ~ 35ms
// then it passes all test cases, but barely (beats 0%)

class Solution {
private:
    const int INF = 100000;

    int mincost[200][200];

    int rec_mincost(vector<vector<int>>& grid, int m, int n, int i, int j) {
        if( mincost[i][j] != -1 )
            return mincost[i][j];

        int local_cost = grid[i][j] != 0 ? 1 : 0;
        if( i == m-1 && j == n-1 )
            return mincost[i][j] = local_cost;

        int ret = INF;

        // go right
        int i_new = i;
        int j_new = j + 1;
        if( j_new < n )
            ret = local_cost + rec_mincost(grid, m, n, i_new, j_new);

        // go down
        i_new = i + 1;
        j_new = j;
        if( i_new < m )
            ret = min(ret, local_cost + rec_mincost(grid, m, n, i_new, j_new));

        return mincost[i][j] = ret;
    }

    // map<int,int> mem;
    unordered_map<int,int> mem;

    int rec(vector<vector<int>>& grid, int m, int n, int i, int j, int k) {
        if( k < mincost[i][j] )
            return -1;

        // possible minor optimization
        //     regardless of k (as long as k >= mincost[i][j], which
        //     we already checked), if we are in the last row or last
        //     column, we can return the respective score

        int local_score = grid[i][j];
        if( i == m-1 && j == n-1 )
            return local_score;

        int key = (i<<18) + (j<<10) + k;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        int local_cost = grid[i][j] != 0 ? 1 : 0;
        int ret = -1;

        // go right
        int i_new = i;
        int j_new = j + 1;
        if( j_new < n ) {
            int a = rec(grid, m, n, i_new, j_new, k - local_cost);
            if( a != -1 )
                ret = local_score + a;
        }

        // go down
        i_new = i + 1;
        j_new = j;
        if( i_new < m ) {
            int b = rec(grid, m, n, i_new, j_new, k - local_cost);
            if( b != -1 )
                ret = max(ret, local_score + b);
        }

        return mem[key] = ret;
    }

public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        // 1 <= m, n <= 200
        // grid[0][0] == 0
        // 0 <= grid[i][j] <= 2

        // idea
        //     we could make a run and for each cell determine
        //     the minimum cost needed to reach (m-1, n-1)
        //     then when we get to a cell we can check quickly
        //     if it is even possible to reach (m-1, n-1)

        memset(mincost,-1,sizeof mincost);
        rec_mincost(grid, m, n, 0, 0);
        if( mincost[0][0] > k )
            return -1;
        // edge case
        if( k == 0 )
            return 0;

        return rec(grid, m, n, 0, 0, k);
    }
};


