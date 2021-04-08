
// 684. Redundant Connection
// https://leetcode.com/problems/redundant-connection/



class Solution {
private:
    bool dfs(int src, int dest, vector<int> t[], int seen[]) {
        if( seen[src] ) return false;
        if( src == dest ) return true;
        seen[src] = 1;

        for(int i = 0; i < t[src].size(); ++i)
            if( dfs(t[src][i],dest,t,seen) ) return true;

        return false;
    }

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        size_t n = edges.size();
        vector<int> t[n+1];
        int seen[n+1]; memset(seen,0,sizeof seen);
        int i,u,v;
        for(i = 0; i < n; ++i) {
            u = edges[i][0];
            v = edges[i][1];
            // we will only add the edge between u and v,
            // if no path already exists between u and v
            if( dfs(u,v,t,seen) ) break;
            t[u].push_back(v);
            t[v].push_back(u);
            memset(seen,0,sizeof seen); // reset for next round
        }

        return edges[i];
    }
};
