
// 3515. Shortest Path in a Weighted Tree
// https://leetcode.com/problems/shortest-path-in-a-weighted-tree/



class Solution {
private:
    // undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n
    vector<vector<vector<int>>> t;

    vector<int> parent;
    vector<int> distance;
    vector<int> subtree_node_count;
    int idx;
    vector<int> st_idx;
    vector<int> st; // segment tree, addition on segments, lazy propagation, point query

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            st[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            st[v] = 0;
        }
    }

    void update(int v, int tl, int tr, int l, int r, int add) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            st[v] += add;
        } else {
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), add);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        }
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl == tr)
            return st[v];
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return st[v] + get(v*2, tl, tm, pos);
        else
            return st[v] + get(v*2+1, tm+1, tr, pos);
    }

    int dfs(vector<vector<vector<int>>>& t, int u, int src, int dist) {
        // if we come to u, we are here the 1st time

        // record parent
        parent[u] = src;
        // record the distance from 1 to us
        distance[idx] = dist;
        // record the pos of u in our segment tree
        st_idx[u] = idx++;

        int nodes_in_subtree = 1; // us

        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i][0];
            if( v == src )
                continue;
            int weight = t[u][i][1];
            nodes_in_subtree += dfs(t, v, u, dist + weight);
        }
        // record count of nodes in our subtree
        return subtree_node_count[u] = nodes_in_subtree;
    }

public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {

        t.resize(n+1);
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            t[u].push_back({v, weight});
            t[v].push_back({u, weight});
        }

        parent.resize(n+1);
        distance.resize(n+1,0);
        subtree_node_count.resize(n+1);
        idx = 0;
        st_idx.resize(n+1);
        st.resize(4*n);

        dfs(t, 1, -1, 0);

        build(distance, 1, 0, n-1);

        // process queries
        vector<int> ans;
        for(int i = 0; i < queries.size(); ++i) {
            if( queries[i][0] == 1 ) {   // update
                int u = queries[i][1];
                int v = queries[i][2];
                int weight = queries[i][3];

                int parent_of_v = parent[v];
                if( parent_of_v != u )
                    swap(u,v);

                // pos of v in segment tree is l for range update
                int idx_v = st_idx[v];
                int l = idx_v;
                int child_count_v = subtree_node_count[v];
                int r = l + child_count_v - 1;

                // current weight of edge u->v
                int idx_u = st_idx[u];
                int dist_one_to_u = get(1, 0, n-1, idx_u);
                int dist_one_to_v = get(1, 0, n-1, idx_v);
                int curr_weight = dist_one_to_v - dist_one_to_u;
                int add = weight - curr_weight;

                update(1, 0, n-1, l, r, add);

            } else {
                int x = queries[i][1];
                int idx_x = st_idx[x];
                int dist_one_to_x = get(1, 0, n-1, idx_x);

                ans.push_back(dist_one_to_x);
            }
        }

        return ans;
    }
};
