
// 3419. Minimize the Maximum Edge Weight of Graph
// https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/




/* when we build our graph we eliminate duplicate edges,
 *   we only keep the smaller one
 * If we reverse all edges and do a DFS and end up with
 * unvisited nodes, then there is no solution
 * if we identify all critical edges, our solution cannot
 * be smaller than any of those
 * if there is a node that has more critical edges than
 * our threshold, then there is no solution

 * it just takes ONE outgoing edge to be able to 'leave' the current node
 * we are not interested in outgoing edges from 0


 */
class Solution {
private:
    int n;
    bool seen[100000];
    vector<unordered_map<int,int>> g;

    void dfs(int u, int max_weight) {
        seen[u] = true;

        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = it->first;
            int weight = it->second;

            if( !seen[v] && weight <= max_weight )
                dfs(v, max_weight);
        }

        return;
    }

    // binary search
    int search(int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        memset(seen,false,sizeof seen);
        dfs(0, mid);
        bool f = true;
        for(int i = 0; i < n; ++i)
            if( !seen[i] ) {
                f = false;
                break;
            }
        if( f ) {
            // can we do better?
            int t = search(s, mid-1);
            return t != -1 ? t : mid;
        }

        return search(mid+1, e);
    }

public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        // edges(u, v, weight) ; 1 <= weight <= 1e6

        this->n = n;
        g.resize(n);

        int mn_weight = 1000000;
        int mx_weight = 1;
        for(auto& edge: edges) {
            // we are reversing the edge!
            int v = edge[0];
            int u = edge[1];
            int weight = edge[2];
            mn_weight = min(mn_weight, weight);
            mx_weight = max(mx_weight, weight);

            auto p = g[u].insert({v,weight});
            if( !p.second )
                p.first->second = min(p.first->second, weight);
        }

        int ans = search(mn_weight, mx_weight);


        return ans;
    }
};
