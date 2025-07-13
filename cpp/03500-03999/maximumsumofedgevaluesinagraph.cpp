
// 3547. Maximum Sum of Edge Values in a Graph
// https://leetcode.com/problems/maximum-sum-of-edge-values-in-a-graph/





class Solution {
private:

public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        // undirected connected graph of n nodes, numbered from 0 to n - 1
        // the graph is connected
        // each node is connected to at most 2 other nodes
        // there are no repeated edges

        int m = edges.size();

        // handle n 1, 2, 3
        // n == 1 is not valid, as edge u != v
        if( n == 2 ) // m has to be 1
            return 2;
        if( n == 3 ) // m either 2 or 3
            return m == 2 ? 9 : 11;


        vector<vector<int>> g(n);
        for(auto& edge :edges) {
            int u = edge[0];
            int v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int nbr_nodes_with_two_edges = 0;
        for(int i = 0; i < n; ++i)
            if( g[i].size() == 2 )
                ++nbr_nodes_with_two_edges;
        cout << "nbr_nodes_with_two_edges " << nbr_nodes_with_two_edges << endl;

        // case all nodes have two edges (it is a ring of nodes)
        // example with 6 nodes
        //  1         2         4         6         5         3
        // (1 * 2) + (2 * 4) + (4 * 6) + (6 * 5) + (5 * 3) + (3 * 1) = 82

        // 8 nodes 1 2 4 6 8 7 5 3
        // int n8 = (1 * 2) + (2 * 4) + (4 * 6) + (6 * 8) + (8 * 7) + (7 * 5) + (5 * 3) + (3 * 1);
        // cout << "n8 " << n8 << endl;
        // 9 nodes 1 2 4 6 8 9 7 5 3
        // int n9 = (1 * 2) + (2 * 4) + (4 * 6) + (6 * 8) + (8 * 9) + (9 * 7) + (7 * 5) + (5 * 3) + (3 * 1);
        // cout << "n9 " << n9 << endl;


        vector<long long> assignment(n);

        // if( nbr_nodes_with_two_edges == n ) {
            assignment[0] = 1;
            // initially we assign 2.. up to the highest even starting at index 1
            // then we assign the largest odd and go down
            int addend = 2;
            int nxt = 2;
            for(int i = 1; i < n; ++i) {
                assignment[i] = nxt;
                if( addend == 2 && nxt + 2 > n ) {
                    // we need to reverse direction
                    if( nxt + 1 == n )
                        nxt = nxt + 1;
                    else
                        nxt = nxt - 1;
                    addend = -2;
                    continue;
                }
                nxt = nxt + addend;
            }
            long long a = 0LL;
            for(int i = 0; i < n; ++i) {
                if( i == n-1 )
                    a += assignment[i] * assignment[0];
                else
                    a += assignment[i] * assignment[i+1];
            }
            // return a;

            return nbr_nodes_with_two_edges == n ? a : a-2LL;

        // }

        // case all nodes have two edges except 2 -> its a line
    }
};
