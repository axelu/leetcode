
// 2467. Most Profitable Path in a Tree
// https://leetcode.com/problems/most-profitable-path-in-a-tree/




class Solution {
private:
    void dfs1(vector<int> g[], int src, int u, int parent[]) {
        parent[u] = src;

        for(int v: g[u])
            if( v != src )
                dfs1(g,u,v,parent);
    }

    int dfs(vector<int> g[], int parent[], int bob_times[], vector<int>& amount, int u, int time) {
        // if Bob was not here ( bob_times[u] == -1 || bob_times[u] > time )
        //    Alice gets the amount (could be negative)
        // if Bob gets here at the same time
        //    Alice gets half the amount (coud be negative)
        // if Bob was already here
        //    Alice gets nothing

        int a = 0;
        if( bob_times[u] == -1 || bob_times[u] > time )
            a = amount[u];
        else if( bob_times[u] == time )
            a = amount[u] / 2;

        int b = -1000000001;

        for(int v: g[u])
            if( v != parent[u] ) {

                int t = dfs(g,parent,bob_times,amount,v,time + 1);
                b = max(b, t);
            }

        return b == -1000000001 ? a : a + b;
    }

public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = edges.size() + 1;

        // we need to record the path of Bob from node 'bob' to 0
        // and mark when Bob traverses a certain node
        // then we can do a DFS on on ALice to determine optimal leaf node

        vector<int> g[n]; // all neighbors including parent

        for(auto& v: edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        int parent[n];
        // populate the parent for each node
        dfs1(g,-1,0,parent);

        /*
        for(int i = 0; i < n; ++i)
            cout << i << ":" << parent[i] << " ";
        cout << endl;
        */

        // Bob now goes from node 'bob' to node 0
        // we need to record the times when Bob traverses each node along the path
        int times[n];memset(times,-1,sizeof times);
        int t = 0;
        while( bob != -1 ) {
            times[bob] = t;
            ++t;
            bob = parent[bob];
        }

        /*
        for(int i = 0; i < n; ++i)
            cout << i << ":" << times[i] << " ";
        cout << endl;
        */

        return dfs(g,parent,times,amount,0,0);
    }
};
