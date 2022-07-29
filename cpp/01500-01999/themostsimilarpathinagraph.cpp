
// 1548. The Most Similar Path in a Graph
// https://leetcode.com/problems/the-most-similar-path-in-a-graph/




/*
define editDistance(targetPath, myPath) {
    dis := 0
    a := targetPath.length
    b := myPath.length
    if a != b {
        return 1000000000
    }
    for (i := 0; i < a; i += 1) {
        if targetPath[i] != myPath[i] {
            dis += 1
        }
    }
    return dis
}
*/

class Solution {
private:

    int mem_d[100][100];
    int mem_nxt[100][100];

    int rec(pair<string,vector<int>> g[],
            vector<string>& targetPath,
            int u,
            int k) {

        if( mem_d[u][k] != -1 )
            return mem_d[u][k];

        int dis = g[u].first == targetPath[k] ? 0 : 1;

        int t = 0;
        int nxt = -1;
        int target_path_sz = targetPath.size();
        if( k < target_path_sz-1 ) {
            t = 1000000000;
            for(int i = 0; i < g[u].second.size(); ++i) {
                int v = g[u].second[i];
                int d = rec(g,targetPath,v,k+1);
                if( d < t ) {
                    t   = d;
                    nxt = v;
                }
            }
        }

        mem_nxt[u][k] = nxt;
        return mem_d[u][k] = dis + t;
    }

public:
    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        // let dp[i][k] be the answer for node i if targetPath would start at targetPath[k]

        pair<string,vector<int>> g[n]; // bi-directional graph
        // setting city names
        for(int i = 0; i < n; ++i)
            g[i].first = names[i];
        // adding edges
        for(auto& v : roads) {
            g[v[0]].second.push_back(v[1]);
            g[v[1]].second.push_back(v[0]);
        }

        int s;
        int t = 100000000;
        // vector<int> ans;
        memset(mem_d,-1,sizeof mem_d);
        for(int u = 0; u < n; ++u) {
            int d = rec(g,targetPath,u,0);
            if( d < t ) {
                t = d;
                s = u;
            }
        }

        int target_path_sz = targetPath.size();
        vector<int> ans(target_path_sz);
        ans[0] = s;
        for(int k = 1; k < target_path_sz; ++k)
            ans[k] = s = mem_nxt[s][k-1];

        return ans;
    }
};
