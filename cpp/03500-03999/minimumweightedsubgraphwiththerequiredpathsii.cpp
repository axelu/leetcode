
// 3553. Minimum Weighted Subgraph With the Required Paths II
// https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/




/* from the hints: binary lifting
 *     https://cp-algorithms.com/graph/lca_binary_lifting.html
 */

class Solution {
private:
    int n, l;
    vector<vector<vector<int>>> adj;

    int timer;
    vector<int> tin, tout;
    vector<vector<int>> up;

    vector<int> distances;

    void dfs(int v, int p, int dist)
    {
        distances[v] = dist;
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i-1]][i-1];

        for (auto& neighbor : adj[v]) {
            int u = neighbor[0];
            int weight = neighbor[1];
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
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // undirected weighted tree with n nodes, numbered from 0 to n - 1
        n = edges.size() + 1;

        adj.resize(n);
        // we will root the tree arbitrarily at node 0
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
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int src1 = queries[i][0]; // src1
            int src2 = queries[i][1]; // src2
            int dest = queries[i][2]; // dest
            // cout << "q " << i << " src1 " << src1 << " src2 " << src2 << " dest " << dest << endl;

            // src1, src2 and dest are just 3 nodes
            // it does not matter which is which
            // we can several cases

            int lca_src1_src2 = lca(src1, src2);
            // cout << "lca_src1_src2 " << lca_src1_src2 << endl;
            // 3 cases
            //     A lca = src1 is ancestor of src2
            //     B lca = src2 is ancestor of src1
            //     C lca is ancestor of src1 and src2
            //           lca != src1 and lca != src2

            if( lca_src1_src2 == src2 ) {
                // cout << "    case B" << endl;
                // lets swap src1 and src2 to make it case A
                swap(src1, src2);
                lca_src1_src2 = src1;
            }

            if( lca_src1_src2 == src1 ) {
                // cout << "    case A lca = src1 is ancestor of src2" << endl;
                // we can have 5 cases
                //     A1 src2 is ancestor of dest implies src1 is ancestor of dest
                //     A2 src1 is ancestor of dest and dest an ancestor of src1
                //     A3 src1 is ancsetor of dest and dest is NOT ancesotr of src2
                //         aka src1 is lca(src2, dest)
                //     A4 dest is ancestor of scr1 implies dest is ancestor of src2
                //     A5 some node is lca of src1 and dest

                int lca_src1_dest = lca(src1, dest); // cout << "    lca_src1_dest " << lca_src1_dest << endl;
                int lca_src2_dest = lca(src2, dest); // cout << "    lca_src2_dest " << lca_src2_dest << endl;

                if( lca_src2_dest == src2 ) {
                    // case A1
                    // cout << "    case A1 " << endl;
                    ans[i] = distances[dest] - distances[src1];

                } else if( lca_src2_dest == src1 ) {
                    // case A3
                    // cout << "    case A3 " << endl;
                    int dist_src1_src2 = distances[src2] - distances[src1];
                    int dist_dest_src1 = distances[dest] - distances[src1];
                    ans[i] = dist_src1_src2 + dist_dest_src1;

                } else if( lca_src2_dest == dest ) {
                    if( lca_src1_dest == src1 ) {
                        // case A2
                        // cout << "    case A2 " << endl;
                        ans[i] = distances[src2] - distances[src1];

                    } else {
                        // case A4
                        // cout << "    case A4 " << endl;
                        ans[i] = distances[src2] - distances[dest];
                    }
                } else {
                    int lca_lca_src2_dest_src1 = lca(lca_src2_dest, src1);
                    if( lca_lca_src2_dest_src1 == lca_src2_dest ) {
                        // case A5
                        // cout << "    case A5 " << endl;
                        int dist_lca_src2_dest_src2 = distances[src2] - distances[lca_src2_dest];
                        int dist_lca_src2_dest_dest = distances[dest] - distances[lca_src2_dest];
                        ans[i] = dist_lca_src2_dest_src2 + dist_lca_src2_dest_dest;

                    } else {
                        // case A5a
                        // cout << "    case A5a " << endl;
                        int dist_src1_src2 = distances[src2] - distances[src1];
                        int dist_lca_src2_dest_dest = distances[dest] - distances[lca_src2_dest];
                        ans[i] = dist_src1_src2 + dist_lca_src2_dest_dest;
                    }

                }

            // } else if( lca_src1_src2 == src2 ) {
            //     cout << "    case B" << endl;

            } else {
                // cout << "    case C lca_src1_src2 " << lca_src1_src2 << endl;
                // we can have 78 cases
                //     C1 src1 is ancestor of dest
                //     C2 src2 is ancestor of dest
                //     C3 lca_src1_src2 is ancestor of dest and
                //        dest is ancestor of src1 and
                //        dest is NOT ancestor of src2
                //     C4 lca_src1_src2 is ancestor of dest and
                //        dest is NOT ancestor of src1 and
                //        dest is ancestor of src2
                //     C5 lca_src1_src2 is ancestor of dest and
                //        dest is NOT ancestor of src1 and
                //        dest is NOT ancestor of src2
                //     C6 dest in ancestor of lca_src1_src2
                //     C7 not C1..C6
                //        some node is ancestor of lca_src1_src2 and dest
                //     C8 lca_src1_src2 == dest

                int lca_src1_dest = lca(src1, dest); // cout << "    lca_src1_dest " << lca_src1_dest << endl;
                int lca_src2_dest = lca(src2, dest); // cout << "    lca_src2_dest " << lca_src2_dest << endl;

                if( lca_src1_dest == src1 ) {
                    // case C1
                    // cout << "    case C1 " << endl;
                    int dist_lca_src1_scr2_dest = distances[dest] - distances[lca_src1_src2];
                    int dist_lca_src1_src2_src2 = distances[src2] - distances[lca_src1_src2];
                    ans[i] = dist_lca_src1_scr2_dest + dist_lca_src1_src2_src2;

                } else if( lca_src2_dest == src2 ) {
                    // case C2
                    // cout << "    case C2 " << endl;
                    int dist_lca_src1_scr2_dest = distances[dest] - distances[lca_src1_src2];
                    int dist_lca_src1_src2_src1 = distances[src1] - distances[lca_src1_src2];
                    ans[i] = dist_lca_src1_scr2_dest + dist_lca_src1_src2_src1;

                } else if( lca_src1_src2 == dest ) {
                    // case C8
                    // cout << "    case C8 " << endl;
                    int dist_lca_src1_src2_src1 = distances[src1] - distances[lca_src1_src2];
                    int dist_lca_src1_src2_src2 = distances[src2] - distances[lca_src1_src2];
                    ans[i] = dist_lca_src1_src2_src1 + dist_lca_src1_src2_src2;

                } else {
                    int lca_lca_src1_src2_dest = lca(lca_src1_src2, dest);
                    if( lca_lca_src1_src2_dest == dest ) {
                        // case C6
                        // cout << "    case C6 " << endl;
                        int dist_dest_src1 = distances[src1] - distances[dest];
                        int dist_dest_src2 = distances[src2] - distances[dest];
                        int dist_dest_lca_src1_src2 = distances[lca_src1_src2] - distances[dest];
                        ans[i] = dist_dest_src1 + dist_dest_src2 - dist_dest_lca_src1_src2;

                    } else if( lca_lca_src1_src2_dest == lca_src1_src2 ) {
                        if( lca_src1_dest == dest || lca_src2_dest == dest ) {
                            // case C3 and case C4
                            // cout << "    case C3 and case C4 " << endl;
                            int dist_lca_src1_src2_src1 = distances[src1] - distances[lca_src1_src2];
                            int dist_lca_src1_src2_src2 = distances[src2] - distances[lca_src1_src2];
                            ans[i] = dist_lca_src1_src2_src1 + dist_lca_src1_src2_src2;

                        // } else if( lca_src2_dest == dest ) {
                            // case C4 (same as C3)

                        } else {
                            if( lca_src1_dest == lca_src1_src2 && lca_src2_dest == lca_src1_src2 ) {
                            // case C5
                                // cout << "    case C5 " << endl;
                                int dist_lca_src1_src2_src1 = distances[src1] - distances[lca_src1_src2];
                                int dist_lca_src1_src2_src2 = distances[src2] - distances[lca_src1_src2];
                                int dist_lca_src1_src2_dest = distances[dest] - distances[lca_src1_src2];
                                ans[i] = dist_lca_src1_src2_src1 + dist_lca_src1_src2_src2 + dist_lca_src1_src2_dest;

                            } else {
                                // case C5a and C5b
                                // cout << "    case C5a and C5b " << endl;
                                int dist_lca_src1_src2_src1 = distances[src1] - distances[lca_src1_src2];
                                int dist_lca_src1_src2_src2 = distances[src2] - distances[lca_src1_src2];
                                int dist_lca_src1_src2_dest = distances[dest] - distances[lca_src1_src2];
                                int d = 0;

                                if( lca_src1_dest == lca_src1_src2 ) {
                                    d = distances[lca_src2_dest] - distances[lca_src1_src2];

                                } else if( lca_src2_dest == lca_src1_src2 ) {
                                    d = distances[lca_src1_dest] - distances[lca_src1_src2];

                                } else {
                                    // we should never get here
                                }

                                ans[i] = dist_lca_src1_src2_src1 + dist_lca_src1_src2_src2 + dist_lca_src1_src2_dest - d;

                            }

                        }

                    } else {
                        // case C7
                        // cout << "    case C7 " << endl;
                        int dist_lca_scr1_src2_src1 = distances[src1] - distances[lca_src1_src2];
                        int dist_lca_src1_src2_src2 = distances[src2] - distances[lca_src1_src2];
                        int dist_lca_lca_src1_src2_dest_lca_src1_src2 = distances[lca_src1_src2] - distances[lca_lca_src1_src2_dest];
                        int dist_lca_lca_src1_src2_dest_dest = distances[dest] - distances[lca_lca_src1_src2_dest];
                        ans[i] = dist_lca_scr1_src2_src1 + dist_lca_src1_src2_src2 + dist_lca_lca_src1_src2_dest_lca_src1_src2 + dist_lca_lca_src1_src2_dest_dest;

                    }
                }
            }
        }

        return ans;
    }
};
