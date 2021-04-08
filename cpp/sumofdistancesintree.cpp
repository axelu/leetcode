
// 834. Sum of Distances in Tree
// https://leetcode.com/problems/sum-of-distances-in-tree/



class Solution {
private:
    int N;

    // post order (children,root)
    void dfs1(int u, vector<int> t[], int parent[], int descCnt[], int sumDist[]) {
        int v; // child
        int n = 0; // number of nodes in subtree
        int d = 0;
        for(int i = 0; i < t[u].size(); ++i) {
            v = t[u][i];
            if( v == parent[u] ) continue; // skip if edge points to parent
            parent[v] = u;
            dfs1(v,t,parent,descCnt,sumDist);
            n += descCnt[v];
            d += sumDist[v];
        }
        descCnt[u] = n + 1; // plus ourselfs
        sumDist[u] = d + n;
    }

    // preorder (root,children)
    void dfs2(int u, vector<int> t[], int parent[], int descCnt[], int sumDist[], vector<int>& ans) {
        int p = parent[u];
        if( parent[u] != -1 ) {  //skip root node
            int pd = sumDist[p];
            // pd is the total distance it will take to reach all nodes one by one
            //    from the parent including us and our descendents
            // what did we contribute to those numbers?
            int un = descCnt[u];
            int ud = sumDist[u];
            int d = pd - (un+ud); // distance to reach all nodes behind parent
            // so to reach all nodes behind the parent:
            int t = (N-un) + d;
            sumDist[u] += t;
            ans[u] = sumDist[u];
        }
        int v; // child
        for(int i = 0; i < t[u].size(); ++i) {
            v = t[u][i];
            if( v == parent[u] ) continue; // skip if edge points to parent
            dfs2(v,t,parent,descCnt,sumDist,ans);
        }
    }

public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        N = n;
        int parent[N]; parent[0] = -1; // pick node 0 as root, arbitrary
        int sumDist[N];
        int descCnt[N];

        vector<int> t[N]; // undirected connected tree
        for(int i = 0; i < N-1; ++i) {
            t[edges[i][0]].push_back(edges[i][1]);
            t[edges[i][1]].push_back(edges[i][0]);
        }

        dfs1(0,t,parent,descCnt,sumDist);

        vector<int> ans(N);
        ans[0] = sumDist[0];
        dfs2(0,t,parent,descCnt,sumDist,ans);
        return ans;
    }
};
