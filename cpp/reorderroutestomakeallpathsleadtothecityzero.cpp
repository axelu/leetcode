
// 1466. Reorder Routes to Make All Paths Lead to the City Zero
// https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/




class Solution {
private:

    // DFS
    int dfs(vector<pair<int,char>> g[], int u, int p) {
        int ret = 0;

        for(int i = 0; i < g[u].size(); ++i) {
            if( g[u][i].first == p ) continue;
            if( g[u][i].second  == 'f' )
                ++ret;
            ret += dfs(g,g[u][i].first,u);
        }
        return ret;
    }

public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<pair<int,char>> g[n];


        for(int i = 0; i < n-1; ++i) {
            g[connections[i][0]].push_back({connections[i][1],'f'});
            g[connections[i][1]].push_back({connections[i][0],'r'});
        }

        return dfs(g,0,-1);
    }
};
