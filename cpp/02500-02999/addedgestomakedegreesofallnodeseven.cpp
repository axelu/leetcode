
// 2508. Add Edges to Make Degrees of All Nodes Even
// https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/




/*
 * if the edges connected to each node is even, there is nothing to do -> ans = true
 * if the count of nodes with odd number of connected edges is greater 4 -> ans = false
 * if we have 1 or 3 nodes with odd number connected edges (not sure how we could)
 *    then we have no solution
 * if the graph is a complete graph ( n * (n-1))/2 edges ) and has min one node with odd connected edges -> ans = false
 *    (note: all nodes have same number of connted edges; as we cannot add repeated edges nor self-loops)
 * if we have two nodes with odd number of connected edges
 *    we could connect them if they don't already have edge connecting them OR
 *    we could find a node with even number of connected edges that neither node has an edge with
 * if we have four nodes with odd number of connected edges
 *    then we have 8 possible pairings to look for
 *
 * so what do we need
 *    we need to know number of edges for each node and which node the are gin
 *    we need to know how many nodes with odd number of connted edges and
 *        how many nodes with even number of connted edges we have
 *    we need to be able to quickly determine if two nodes are connected by an edge
 */
class Solution {
private:
    bool have_direct_edge(unordered_set<int> g[], int u, int v) {
        return g[u].find(v) != g[u].end();
    }

    bool can_connect_to_even(unordered_set<int> g[], vector<int>& even, int u, int v) {
        // TODO optimize, think about a bool array even nodes of size n+1
        // then just loop from 1 to including n, if i in neither (two pointers) in u or v list (sorted),
        // then we have a winner, that approach maybe faster then this here
        for(int node: even)
            if( g[node].find(u) == g[node].end() && g[node].find(v) == g[node].end() )
                return true;

        return false;
    }
public:
    bool isPossible(int n, vector<vector<int>>& edges) {
        // n nodes numbered from 1 to n
        unordered_set<int> g[n+1];
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            g[u].insert(v);
            g[v].insert(u);
        }

        vector<int> even;
        vector<int> odd;
        for(int u = 1; u <= n; ++u) {
            if( g[u].size() % 2 == 0 )
                even.push_back(u);
            else
                odd.push_back(u);
        }

        if( odd.size() == 0 )
            return true;

        if( odd.size() > 4 || odd.size() == 1 || odd.size() == 3 )
            return false;

        unsigned long long nbr_edges_complete_graph = (unsigned long long)n * (n-1) / 2ULL;
        if( nbr_edges_complete_graph == edges.size() )
            return false;

        if( odd.size() == 2 ) {
            // if the two nodes don't have a direct edge, we can connect them
            if( !have_direct_edge(g,odd[0],odd[1]) )
                return true;

            // we need to find a node with even number of connected edges that
            // does not have an edge with either u or v
            return can_connect_to_even(g,even,odd[0],odd[1]);
        }

        // odd.size() == 4
        // connect the differnt possible pairs
        // 1 -> 2 and 3 -> 4
        // 1 -> 3 and 2 -> 4
        // 2 -> 3 and 1 -> 4
        if( ( !have_direct_edge(g,odd[0],odd[1]) && !have_direct_edge(g,odd[2],odd[3]) ) ||
            ( !have_direct_edge(g,odd[0],odd[2]) && !have_direct_edge(g,odd[1],odd[3]) ) ||
            ( !have_direct_edge(g,odd[1],odd[2]) && !have_direct_edge(g,odd[0],odd[3]) ) )
             return true;

        return false;
    }
};
