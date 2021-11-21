
// 1615. Maximal Network Rank
// https://leetcode.com/problems/maximal-network-rank/


class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        // 2 <= n <= 100
        auto m = roads.size();
        if( m == 0 ) return 0;
        if( m == 1 ) return 1;

        int c[100][101]; // matrix to record connections between cities
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n+1; ++j)
                c[i][j] = 0;

        for(int i = 0; i < roads.size(); ++i) {
            c[roads[i][0]][roads[i][1]] = 1;
            c[roads[i][1]][roads[i][0]] = 1;
        }

        // sum of connections to each city
        int r = 0;
        for(int i = 0; i < n; ++i) {
            r = 0;
            for(int j = 0; j < n; ++j)
                r += c[i][j];
            c[i][100] = r;
        }

        // brute force ( n max 100): get maximum pair of cities
        r = 0;
        int t1 = 0, t2 = 0;
        for(int i = 0; i < n - 1; ++i) {
            t1 = c[i][100];
            for(int j = i + 1; j < n; ++j) {
                t2 = c[j][100] + t1;
                if( c[i][j] == 1 ) --t2;
                r = max(r,t2);
            }
        }

        return r;
    }
};
