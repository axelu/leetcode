
// 3310. Remove Methods From Project
// https://leetcode.com/problems/remove-methods-from-project/

/*

4
1
[[1,2],[0,1],[3,2]]
5
0
[[1,2],[0,2],[0,1],[3,4]]
3
2
[[1,2],[0,1],[2,0]]
10
0
[[1,2],[2,3],[3,4],[4,0],[0,5],[5,6],[6,7],[7,8],[9,3]]
10
1
[[1,2],[2,3],[3,4],[4,0],[0,5],[5,6],[6,7],[7,8],[9,3]]
11
0
[[1,2],[2,3],[3,4],[4,0],[0,5],[5,6],[6,7],[7,8],[9,3],[0,10]]
4
2
[[1,2],[0,1],[2,0],[3,0]]
7
1
[[0,1],[1,2],[2,3],[6,2],[4,5]]
7
1
[[0,1],[1,2],[2,3],[4,5]]
4
1
[[0,1],[1,2],[2,3]]
5
1
[[0,1],[1,2],[2,3]]
6
1
[[0,1],[1,2],[2,3],[4,5]]
4
3
[[3,2],[1,3],[3,1],[2,0],[0,2]]

*/




class Solution {
private:
    // disjoint-set path compression size
    int * parent;
    int * size;

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

    void dfs(vector<int> g[], int u, int src, bool seen[], bool do_unite) {
        seen[u] = true;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( v == src )
                continue;

            if( do_unite )
                unite(u, v);
            if( seen[v] )
                continue;
            dfs(g, v, u, seen, do_unite);
        }

        return;
    }

public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<int> g[n];
        for(auto& edge: invocations)
            g[edge[0]].push_back(edge[1]);

        int _parent[n]; parent = _parent;
        int _size[n]; size = _size;
        for(int i = 0; i < n; ++i) {
            parent[i] = i;
            size[i] = 1;
        }

        bool seen[n];memset(seen,false,sizeof seen);
        for(int u = 0; u < n; ++u) {
            if( seen[u] )
                continue;
            dfs(g, u, -1, seen, true);
        }

        // root of k
        int root_k = find(k); // cout << "root_k " << root_k << endl;
        /*
        for(int i = 0; i < n; ++i)
            cout << i << ":" << parent[i] << " ";
        cout << endl;
        */

        // if we have a node i where find[i] != root_k,
        // then node i remains

        // additionally, we can remove all nodes i where find[i] == root_k
        // if they are reachable from node k
        memset(seen,false,sizeof seen);
        dfs(g,k,-1,seen,false);

        bool keep = false;
        for(int i = 0; i < n; ++i)
            if( find(i) == root_k && !seen[i] ) {
                keep = true;
                break;
            }

        vector<int> ans;
        for(int i = 0; i < n; ++i)
            if( find(i) != root_k )
                ans.push_back(i);
            else if( keep )
                ans.push_back(i);

        return ans;
    }
};
