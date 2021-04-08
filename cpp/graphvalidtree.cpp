
// 261. Graph Valid Tree
// https://leetcode.com/problems/graph-valid-tree/



class Solution {
    bool dfs(int v, int from, vector<int> t[], int seen[]) {
        seen[v] = 1;
        for(int i = 0; i < t[v].size(); ++i) {
            if( t[v][i] == from ) continue;
            if( seen[t[v][i]] ) return false;
            if( !dfs(t[v][i],v,t,seen) ) return false;
        }
        return true;
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if( n == 1 ) return true;

        vector<int> t[n];
        for(int i = 0; i < edges.size(); ++i) {
            t[edges[i][0]].push_back(edges[i][1]);
            t[edges[i][1]].push_back(edges[i][0]);
        }
        int seen[n]; memset(seen,0,sizeof seen);
        if( !dfs(0,-1,t,seen) ) return false;
        // check if we actually visited every node
        for(int i = 0; i < n; ++i)
            if( !seen[i] ) return false;
        return true;
    }
};
