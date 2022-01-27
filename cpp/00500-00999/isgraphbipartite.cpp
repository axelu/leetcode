
// 785. Is Graph Bipartite?
// https://leetcode.com/problems/is-graph-bipartite/
// day 14 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3639/



class Solution {
private:
    bool dfs(vector<vector<int>>& g, int u, int seen[], int side[]) {
        seen[u] = 1;
        int v;
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i];
            if( side[v] != -1 ) {
                if( side[v] == side[u] ) return false;
            } else {
                side[v] = !side[u];
                if( !dfs(g,v,seen,side) ) return false;
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& g) {
        // the given graph is an undirected graph,
        int n = g.size(); // 1 <= graph.length <= 100

        int seen[n]; memset(seen,0,sizeof seen);
        int side[n]; memset(side,-1,sizeof side);
        // graph could have one or more connected components
        // hence we will start a dfs from evey unvisited node
        for(int i = 0; i < n; ++i) {
            if( !seen[i] ) {
                side[i] = 0; // assign a side
                if( !dfs(g,i,seen,side) ) return false;
            }
        }
        return true;
    }
};
