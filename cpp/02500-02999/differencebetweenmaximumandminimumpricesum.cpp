
// 2538. Difference Between Maximum and Minimum Price Sum
// https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/






/* example 2 nodes
 * n = 2, edges = {{0,1}}, price = {5,6}
 * ans = 6 -> answer is the total of a path between two leaves minus the smaller leaf
 * example 3 nodes
 * n = 3, edges = {{0,1},{1,2}}, price = {3,5,6}
 * ans = 11 -> answer is the total of a path between two leaves minus the smaller leaf
 * so we need to maximize the path between two leaves minus the smaller leaf
 * leaf - node - node ... - u - v ... - node - node - leaf
 *                              *
 * ------------------------------------------------          ans OR
 *        -------------------------------------------------   ans depending on which leaf is smaller
 * let us assume we track the maximum cost of path to a node v from the leaf with_leaf[v] and
 * the maximum cost of the path without the leaf without_leaf[v]
 * we have two options for the cost of the path to v when we arrive at v from u
 *   with_leaf[u] + without_leaf[v]   OR
 *   without_leaf[u] + with_leaf[v]
 * so we will start from leafs and track both costs
 * if we arrive at a node and have covererd all subtrees, we have the answer for that node
 */
class Solution {
private:

    long long ans;

    pair<long long, long long> dfs(vector<int> t[], int u, int src, long long with_leaf, long long without_leaf,
                                   vector<int>& price) {

        // if src == -1 we are just starting out
        // eventually we will be at a node in which all culminates

        bool is_leaf = t[u].size() == 1;

        if( is_leaf ) {
            if( src == -1 ) {
                int v = t[u][0];
                auto p = dfs(t, v, u, (long long)price[u], 0LL, price);
                long long subtree_with_leaf = p.first;
                long long subtree_without_leaf = p.second;

                ans = max({ans, subtree_with_leaf, (long long)price[u] + subtree_without_leaf});
                return {-1LL, -1LL}; // return not used

            } else {

                ans = max({ans, with_leaf, (long long)price[u] + without_leaf});
                return {(long long)price[u], 0LL};
            }

        } else {
            long long mx_ret_w_leaf  = 0LL;
            long long mx_ret_wo_leaf = 0LL;

            for(auto it = t[u].begin(); it != t[u].end(); ++it) {
                int v = *it;

                if( v == src )
                    continue;

                // use as input to any subtree the max we have seen from any other subtree including from when node u was reached
                auto p = dfs(t, v, u, max(with_leaf, mx_ret_w_leaf) + (long long)price[u], max(without_leaf, mx_ret_wo_leaf) + (long long)price[u], price);
                long long subtree_with_leaf = p.first;
                long long subtree_without_leaf = p.second;

                // return whatever any subtree yielded as the max
                mx_ret_w_leaf = max(mx_ret_w_leaf, subtree_with_leaf);
                mx_ret_wo_leaf = max(mx_ret_wo_leaf, subtree_without_leaf);



                ans = max({ans , without_leaf + (long long)price[u] + subtree_with_leaf,
                                 with_leaf + (long long)price[u] + subtree_without_leaf});
            }
            return {mx_ret_w_leaf + (long long)price[u], mx_ret_wo_leaf + (long long)price[u]};
        }
    }

public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        // undirected and initially unrooted tree with n nodes indexed from 0 to n - 1
        // n-1 edges

        vector<int> t[n];
        for(auto edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        ans = 0LL;
        dfs(t, 0, -1, -1LL, -1LL, price);

        return ans;
    }
};




/*
1
[]
[3]
2
[[0,1]]
[5,6]
3
[[0,1],[1,2]]
[3,5,6]
*/
