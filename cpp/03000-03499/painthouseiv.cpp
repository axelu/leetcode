
// 3429. Paint House IV
// https://leetcode.com/problems/paint-house-iv/






class Solution {
private:
    const long long INF = 10000000001;

    // worst case n = 1e5, 3 colors
    // pos * pre * nxt = 100000/2 * 3 * 3 = 450000
    long long mem[50000][3][3];

    long long rec(vector<vector<int>>& cost, int n, int pos, int pre, int nxt) {
        // pos, pre = color pos-1, nxt = color (n-1) - pos + 1

        int n2 = n / 2;
        if( pos == n2 )
            return 0LL;

        if( pos > 0 && mem[pos][pre][nxt] != -1LL )
            return mem[pos][pre][nxt];

        long long ret = INF;

        for(int c1 = 0; c1 < 3; ++c1) {
            // can we paint house at pos in color c1 based on house to our left?
            if( pre == c1 )
                continue;
            for(int c2 = 0; c2 < 3; ++c2) {
                // Houses equidistant from the ends of the row
                // are not painted the same color aka
                if( c2 == c1 )
                    continue;
                if( c2 == nxt )
                    continue;

                long long _cost = cost[pos][c1] + cost[(n-1)-pos][c2];
                ret = min(ret, _cost + rec(cost, n, pos+1, c1, c2));
            }
        }

        if( pos > 0 )
           mem[pos][pre][nxt] = ret;
        return ret;
    }

public:
    long long minCost(int n, vector<vector<int>>& cost) {
        // it is guaranteed that n is even

        memset(mem,-1,sizeof mem);
        return rec(cost, n, 0, -1, -1);
    }
};
