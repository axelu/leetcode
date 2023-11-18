
// 2925. Maximum Score After Applying Operations on a Tree
// https://leetcode.com/problems/maximum-score-after-applying-operations-on-a-tree/




class Solution {
private:
    long long dfs1(vector<int> g[], vector<int>& values, int u, bool seen[], long long sum[]) {
        seen[u] = true;

        long long ret = values[u];
        for(int v: g[u]) {
            if( !seen[v] )
                ret += dfs1(g,values,v,seen,sum);
        }

        return sum[u] = ret;
    }

    long long dfs2(vector<int> g[], vector<int>& values, int u, bool seen[], long long sum[]) {
        seen[u] = true;

        // if our current node is a leave, return 0,
        // basically stating that we did NOT take it to ensure the constraint
        if( sum[u] == values[u] )
            return 0LL;


        // we have a choice
        //     don't take the current node OR
        //     take the current node

        long long a = sum[u] - values[u];

        long long b = values[u];
        for(int v: g[u]) {
            if( !seen[v] )
                b += dfs2(g,values,v,seen,sum);
        }

        return max(a,b);
    }

public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        int n = edges.size() + 1;


        vector<int> g[n]; // undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0
        for(vector<int>& edge: edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        bool seen[n];

        memset(seen,false,sizeof seen);
        long long sum[n]; // sum[i] of subtree rooted at i (including value[i])
        dfs1(g,values,0,seen,sum);

        memset(seen,false,sizeof seen);
        return dfs2(g,values,0,seen,sum);
    }
};
