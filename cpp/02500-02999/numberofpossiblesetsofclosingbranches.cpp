
// 2959. Number of Possible Sets of Closing Branches
// https://leetcode.com/problems/number-of-possible-sets-of-closing-branches/





// resources
// https://stackoverflow.com/questions/10458267/what-is-the-best-way-to-loop-through-integers-with-at-most-k-bits-on
// https://stackoverflow.com/questions/8281951/bit-hack-to-generate-all-integers-with-a-given-number-of-1s
// http://graphics.stanford.edu/~seander/bithacks.html#NextBitPermutation
// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm

class Solution {
private:
    void printBinary(int x) {
        for(int i = 9; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    int number_of_0_bits_after_least_significant_1_bit(int v) {
        int ret = 0;
        for(int i = 0; i < 10; ++i) {
            if( v & 1 )
                break;
            ++ret;
            v >>= 1;
        }
        return ret;
    }

    int next_permutation(unsigned int v) {
        //  v current permutation of bits
        unsigned int w; // next permutation of bits
        unsigned int t = v | (v - 1); // t gets v's least significant 0 bits set to 1
        // Next set to 1 the most significant bit to change,
        // set to 0 the least significant ones, and add the necessary 1 bits.
        // w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
        w = (t + 1) | (((~t & -~t) - 1) >> (number_of_0_bits_after_least_significant_1_bit(v) + 1));
        return w;
    }

    int dist[10][10];
    int prev[10][10];
    vector<int> paths[10][10];

    unordered_map<int,int> g[10];

    // Dijkstra's algorithm
    int shortestPath(int s, int d, int n, int removed_nodes) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[n+1];
        for(int i = 0; i < n+1; ++i)
            A[i] = 100000001;

        // push our source vertex into priority queue
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            for(auto it = g[u].begin(); it != g[u].end(); ++it) {
                v = it->first;
                weight = it->second;

                if( (removed_nodes>>v) & 1 )
                    continue;

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        return A[d];
    }

    void floyd_warshall_with_path_reconstruction(vector<vector<int>>& edges, int n) {
        // Floyd-Warshall for an undirected connected weighted graph with path reconstructions
        int i,j,k;
        long u,v,w;

        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j) {
                dist[i][j] = 100000001;
                prev[i][j] = -1;
            }

        for(i = 0; i < edges.size(); ++i) {
            u = edges[i][0];
            v = edges[i][1];
            w = edges[i][2];
            if( w < dist[u][v] ) {
                dist[u][v] = w;
                prev[u][v] = u;
                dist[v][u] = w;
                prev[v][u] = v;
            }
        }

        for(i = 0; i < n; ++i) {
            dist[i][i] = 0;
            prev[i][i] = i;
        }

        for(k = 0; k < n; ++k)
            for(i = 0; i < n; ++i)
                for(j = 0; j < n; ++j)
                    if( dist[i][j] > dist[i][k] + dist[k][j] ) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        prev[i][j] = prev[k][j];
                    }

        // create shortest path vector for all pairs i,j
        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j)
                paths[i][j] = path(i,j);

        return;
    }

    vector<int> path(int u, int v) {
        if( prev[u][v] == -1 )
            return {};

        vector<int> ret{v};
        while( u != v ) {
            v = prev[u][v];
            if( v == -1 )
                return {};
            ret.push_back(v);
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }

    bool is_possible_closing_set(int removed_nodes, int n, int maxDistance) {

        for(int i = 0; i < n-1; ++i) {
            if( (removed_nodes>>i) & 1 )
                continue;
            for(int j = i+1; j < n; ++j) {
                if( (removed_nodes>>j) & 1 )
                    continue;

                // neither i nor j are removed

                // check if any nodes on their shortest path are removed
                bool node_in_path_removed = false;
                for(int k: paths[i][j]) {
                    if( (removed_nodes>>k) & 1 ) {
                        node_in_path_removed = true;
                        break;
                    }
                }

                int distance = dist[i][j];

                if( node_in_path_removed ) {
                    // we need to find the current shortest path between i and j
                    distance = shortestPath(i,j,n,removed_nodes);
                }

                if( distance > maxDistance )
                    return false;
            }
        }

        return true;
    }

public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        // 1 <= n <= 10
        if( n == 1 )
            return 2;

        // we know removing all branches respectively no branch left yields 1 possible set of closing branches
        // we know removing all but 1 branch respectively 1 branch left yields n possible sets of closing branches
        // we need to find the remaining sets meeting the criteria closing 0 to n-2 branches

        // Floyd-Warshall for an undirected connected weighted graph with path reconstructions
        floyd_warshall_with_path_reconstruction(roads,n);

        if( n == 2 )
            return dist[0][1] <= maxDistance ? 4 : 3;

        // also build an undirected weighted graph
        for(vector<int>& road: roads) {
            int u = road[0];
            int v = road[1];
            int weight = road[2];

            auto f = g[u].find(v);
            if( f == g[u].end() ) {
                g[u].insert({v,weight});
                g[v].insert({u,weight});
            } else {
                // only keep the shorter road
                if( f->second > weight ) {
                    f->second = weight;
                    g[v][u] = weight;
                }
            }
        }

        vector<int> masks;
        masks.push_back(0);
        int branches_to_remove_max = n - 2;
        for(int branches_to_remove = 1 ; branches_to_remove <= branches_to_remove_max; ++branches_to_remove) {
            int p = pow(2,branches_to_remove) - 1;
            int mx = pow(2,n) - 1;
            while( p < mx ) {
                // printBinary(p);
                masks.push_back(p);
                p = next_permutation(p);
            }
        }

        int ans = 1 + n;

        // masks represents all possible set of nodes that could be removed
        // for each set we determine for each pair of remaining nodes if distance is <= maxDistance still
        for(int mask: masks)
            ans += is_possible_closing_set(mask,n,maxDistance);

        return ans;
    }
};
