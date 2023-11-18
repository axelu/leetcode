
// 2603. Collect Coins in a Tree
// https://leetcode.com/problems/collect-coins-in-a-tree/





/*
 *  https://stackoverflow.com/questions/51461057/topological-sort-on-directed-and-undirected-graphs-using-dfs-algorithm
 *      see second answer talks about topological sort on an undirected graph using a modified version of Kahn's algorithm
 *  Kahn's algorithm for a topological sort
 *  https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
 */
class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        // undirected and unrooted tree
        int n = edges.size() + 1;
        if( n <= 5 )
            return 0;

        unordered_map<int,unordered_set<int>> g; // undirected and unrooted tree
        for(auto& edge: edges) {
            g[edge[0]].insert(edge[1]);
            g[edge[1]].insert(edge[0]);
        }

        queue<int> q;
        for(auto p: g)
            if( coins[p.first] == 0 && p.second.size() == 1 )
                q.push(p.first);

        while( !q.empty() ) {
            int u = q.front();
            q.pop();
            for(int parent: g[u] ) {
                g[parent].erase(u);
                if( coins[parent] == 0 && g[parent].size() == 1 )
                    q.push(parent);
            }
            // cout << "erasing leave node NOT holding a coin " << u << " from tree" << endl;
            g.erase(u);
        }

        // all leave nodes aka nodes with only one edge, that remain in our tree, have a coin.
        // we only need to go to their 'grand parent' in order to collect the coins.

        // we could determine a centroid of the graph using a modified version of Kahn's topological sort algorithm
        // then root our tree in said centroid and use DFS to determine the depth of each node
        // then we could use another DFS and count the edges we traverse till we reached all nodes whos
        // subtree has a depth of 2

        // another idea is to remove the remaining leaves and their parents
        // the parent can only be removed if it has one edge after removal of our own edge
        // we need to leave the dangling edge on the grandparent, because the grand parent
        // maybe the parent of a leave and in this case must not be deleted

        // reuse our queue to hold our leaves
        for(auto p: g)
            if( g[p.first].size() == 1 )
                q.push(p.first);
        while( !q.empty() ) {
            int u = q.front();
            q.pop();
            int parent = *g[u].begin();
            // cout << "erasing leave node holding a coin " << u << " from tree" << endl;
            g.erase(u);

            g[parent].erase(u);
            if( g[parent].size() == 1 ) {
                // cout << "erasing parent node " << parent << " from tree" << endl;
                g.erase(parent);
            }
        }

        // the remaining nodes in the tree must be visited
        return g.size() > 0 ? (g.size() - 1) * 2 : 0;
    }
};
