
// 3493. Properties Graph
// https://leetcode.com/problems/properties-graph/





class Solution {
private:
    int intersect(vector<vector<bool>>& distinct, int i, int j) {
        int ret = 0;
        for(int k = 1; k <= 100; ++k)
            if( distinct[i][k] && distinct[j][k] )
                ++ret;
        return ret;
    }

    void dfs(vector<vector<int>>& g, int u, vector<bool>& seen) {
        seen[u] = true;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( seen[v] )
                continue;
            dfs(g, v, seen);
        }

        return;
    }

public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();      // 1 <= n == properties.length <= 100
        int m = properties[0].size();   // 1 <= m == properties[i].length <= 100; 1 <= properties[i][j] <= 100

        vector<vector<bool>> distinct(n, vector<bool>(101,false));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                distinct[i][properties[i][j]] = true;

        vector<vector<int>> g(n);
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j) {
                int t = intersect(distinct, i, j);
                if( t >= k ) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }

        int cc = 0; // connected components
        vector<bool> seen(n, false);
        for(int u = 0; u < n; ++u) {
            if( !seen[u] ) {
                ++cc;
                dfs(g, u, seen);
            }
        }

        return cc;
    }
};
