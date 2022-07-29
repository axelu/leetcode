
// 2316. Count Unreachable Pairs of Nodes in an Undirected Graph
// https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/




class Solution {
private:
    int dfs(vector<int> g[], int u, int seen[]) {

        seen[u] = 1;

        int ret = 1;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( !seen[v] )
               ret += dfs(g,v,seen);
        }
        return ret;
    }

public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        // determine nbr of connected components and nbr of vertices in each

        if( edges.size() == 0 )  // edge case
            return (long long)n * (n-1) / 2;

        vector<int> g[n]; // undirected graph
        for(auto& v : edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        int seen[n];memset(seen,0,sizeof seen);
        vector<long long> v; // nbr vertices in connected components
        for(int u = 0; u < n; ++u) {
            if( !seen[u] )
                v.push_back(dfs(g,u,seen));
        }

        int v_sz = v.size(); // == nbr of connected components
        // cout << v_sz << endl;
        if( v_sz == 1 )      // edge case
            return 0;

        /*
        // debug
        for(int x : v)
            cout << x << " ";
        cout << endl;
        */

        long long ans = 0LL;
        for(int i = 0; i < v_sz-1; ++i)
            for(int j = i+1; j < v_sz; ++j)
                ans += v[i]*v[j];

        return ans;
    }
};
