
// 1042. Flower Planting With No Adjacent
// https://leetcode.com/problems/flower-planting-with-no-adjacent/




class Solution {
private:
   void dfs(vector<int> g[], int u, int seen[], vector<int>& ans) {

        seen[u] = 1;
        int v;

        // each node has the choice to assign itself color 1,2,3 or 4
        // we will pick a possible color based on colors already assigned to
        // our incoming and outgoing connections, if that color assignment
        // does not lead to success, we need to try another color

        int neighboorCount = g[u].size();

        int taken[] = {0,0,0,0,0};
        for(int i = 0; i < neighboorCount; ++i) {
            v = g[u][i];
            if( ans[v-1] != -1 ) {
                taken[ans[v-1]] = 1;
            }
        }

        for(int c = 1; c <= 4; ++c) {
            if( taken[c] ) continue;

            ans[u-1] = c; // assign ourselfs a color not taken by our neighbors yet

            for(int i = 0; i < g[u].size(); ++i) {
                v = g[u][i];
                if( !seen[v] ) {
                    dfs(g,v,seen,ans);

                }
            }
            break;
        }

    }

public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {

        int u,v;

        // undirected graph
        vector<int> g[n+1];

        // edge list -> adjacency list
        for(int i = 0; i < paths.size(); ++i) {
            u = paths[i][0];
            v = paths[i][1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        int seen[n+1];memset(seen,0,sizeof seen);


        vector<int> ans(n,-1);
        for(int i = 1; i <= n; ++i) {

            if( !seen[i] ) {
                dfs(g,i,seen,ans);

            }
        }

        return ans;
    }
};
