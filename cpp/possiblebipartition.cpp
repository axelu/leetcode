
// 886. Possible Bipartition
// https://leetcode.com/problems/possible-bipartition/


// see also
// https://leetcode.com/problems/is-graph-bipartite/
class Solution {
private:
    bool dfs(vector<int> g[], int u, int seen[], int side[]) {
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
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        // undirected graph with one or more connected components
        vector<int> g[N+1];
        for(int i = 0; i < dislikes.size(); ++i) {
            g[dislikes[i][0]].push_back(dislikes[i][1]);
            g[dislikes[i][1]].push_back(dislikes[i][0]);
        }

        int seen[N+1]; memset(seen,0,sizeof seen);
        int side[N+1]; memset(side,-1,sizeof side);
        // graph could have one or more connected components
        // hence we will start a dfs from evey unvisited node
        for(int i = 1; i <= N; ++i) {
            if( !seen[i] ) {
                side[i] = 0; // assign a side
                if( !dfs(g,i,seen,side) ) return false;
            }
        }
        return true;
    }
};
