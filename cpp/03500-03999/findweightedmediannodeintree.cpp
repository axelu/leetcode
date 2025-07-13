
// 3585. Find Weighted Median Node in Tree
// https://leetcode.com/problems/find-weighted-median-node-in-tree/






/*  example
    let A be an ancestor of B, and B an ancestor of C
    (A being node 0, B being node 1, C being node 2)
    n = 3, edges = [[0,1,3],[1,2,2]], queries [[0,2],[2,0]]
    A --3--> B --2--> C
    query A,C answer B
    query C,A answer A

    example
    A --3--> B --2--> C --4--> D
    query A,D answer C
    query D,A answer B

    idea
    - we do a DFS from the root
    - if we arrive at a given node, we process the queries
      where either that node is the start or the end
    - we keep track of the nodes in our path
    - we keep track of the aggregated distance from root
      to every node in our path (like a prefixSum)
    we arrived at u
    query v u
        case: we have seen v aka root -> ... -> v -> ... u
              we can use the prefixSum and a lower bound binary search to find the answer
        case: we have NOT seen v yet
              we cannot yet process the query and we will wait till we arrive at v

    query u v
        case: we have seen v aka root -> ... -> v -> ... u
              we can use the prefixSum and a greatest-less-than-or-equal binary search to find the answer
        case: we have NOT seen v yet
              we cannot yet process the query and we will wait till we arrive at v

    above works if u is ancestor of v OR v is ancestor of u
    it will not work if u != ancesotr v and v != ancestor u
    respectively if there is another node that is the [lowest] common ancestor for u and v
    soooo
    if we keep track distance from root, we would know
    distance between u and v = root->u + root->v - 2*(root->lca(u,v))
    it would allow us to determine in which leg (lca->u or lca->v) the answer is
    and we could just start traveling from lca in that leg to find the answer
    but that seems ineffecient
    maybe we do two passes:
    pass 1 we collect what is described so far
    then we change the queries in place to exactly what we are after
        flip if needed and put target value and type (lb or gltore)
        in fact, the query will change and will involve the lca instead of one of the two nodes
        there are 4 cases

    pass 2
        if we arrive at a given node, process all queries where target is that node
        we guaranteed that the source is in our current path




 */
class Solution {
private:
    // lowest common ancestor lca binary lifting
    // https://cp-algorithms.com/graph/lca_binary_lifting.html

    int n, l;
    vector<vector<vector<int>>> adj;

    int timer;
    vector<int> tin, tout;
    vector<vector<int>> up;

    vector<long long> distances;

    void dfs(int v, int p, long long dist)
    {
        distances[v] = dist;
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i-1]][i-1];

        for (auto& neighbor : adj[v]) {
            int u = neighbor[0];
            long long weight = (long long)neighbor[1];
            if (u != p)
                dfs(u, v, dist + weight);
        }

        tout[v] = ++timer;
    }

    bool is_ancestor(int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    vector<pair<long,int>> _distances;
    vector<int> ans;
    vector<vector<vector<long long>>> _queries;

    // binary search lower bound recursive
    int search(int s, int e, long long target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( _distances[mid].first >= target ) {
            // can we do better?
            int t = search(s, mid-1, target);
            return t != -1 ? t : mid;
        }

        return search(mid+1, e, target);
    }

    void dfs2(int v, int p, long long dist) {
        _distances.push_back({dist, v});


        // answer all queries for v
        for(auto& q: _queries[v]) {
            int q_idx = q[0];
            long long target = q[1];

            int t = search(0, _distances.size()-1, target);
            if( q[2] == -1 && _distances[t].first != target )
                --t;

            ans[q_idx] = _distances[t].second;
        }

        for (auto& neighbor : adj[v]) {
            int u = neighbor[0];
            long long weight = (long long)neighbor[1];
            if (u != p)
                dfs2(u, v, dist + weight);
        }

        // backtrack
        _distances.pop_back();

        return;
    }

public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1
        this->n = n;

        adj.resize(n);
        for(auto& edge :edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            adj[u].push_back({v,weight});
            adj[v].push_back({u,weight});
        }

        tin.resize(n);
        tout.resize(n);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n, vector<int>(l + 1));
        distances.resize(n);
        dfs(0, 0, 0);

        // process queries
        int q_sz = queries.size();
        ans.resize(q_sz);

        _queries.resize(n);

        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int v = queries[i][1];

            if( u == v ) {
                ans[i] = u;
                continue;
            }
            // neighbors ?
            if( up[v][0] == u ) {
                ans[i] = v;
                continue;
            }
            if( up[u][0] == v ) {
                ans[i] = v;
                continue;
            }

            int _lca = lca(u,v);
            // cout << "q " << i << " u " << u << " v " << v << " lca " << _lca << endl;

            if( _lca == u ) {
                // u is an ancestor of v
                // when we arrive at v, we can answer this query
                long long dist = distances[v] - distances[u];
                long long target = distances[u] + ceil(dist / 2.0);
                _queries[v].push_back({i,target,0});

            } else if( _lca == v ) {
                // v is ancestor of u
                // when we arrive at u, we can answer this query
                long long dist = distances[u] - distances[v];
                long long target = distances[v] + floor(dist / 2.0);
                _queries[u].push_back({i,target,-1});

            } else {
                // _lca is the ancestor of u and v
                // our answer is either between u and _lca or
                // between _lca and v

                long long dist_u_lca = distances[u] - distances[_lca];

                long long dist_lca_v = distances[v] - distances[_lca];

                long long dist_u_v = dist_u_lca + dist_lca_v;

                long long _target = ceil(dist_u_v / 2.0);

                if( _target >= dist_u_lca ) {
                    // cout << "our answer is between _lca and v" << endl;
                    // we can answer when we arrive at v
                    long long target = _target - dist_u_lca + distances[_lca];
                    _queries[v].push_back({i,target,0});

                } else {
                    // cout << "our answer is between u and _lca" << endl;
                    // we can answer when we arrive at u
                    long long target = dist_u_lca - _target + distances[_lca];
                    _queries[u].push_back({i,target,-1});
                }
            }
        }

        // dfs to answer the remaining queries via a binary search lower bound
        dfs2(0, 0, 0);

        return ans;
    }
};
