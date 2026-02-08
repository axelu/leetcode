
// 3778. Minimum Distance Excluding One Maximum Weighted Edge
// https://leetcode.com/problems/minimum-distance-excluding-one-maximum-weighted-edge/


// based on hints

class Solution {
public:
    long long minCostExcludingMax(int n, vector<vector<int>>& edges) {
        // 1 <= n <= 50000
        // edges[i] = [ui, vi, wi]
        // 1 <= wi <= 50000 ??? this is not reality, test case 913 uses greater values
        // weighted connected simple undirected graph
        // A simple graph is a type of graph that does not have multiple
        // edges between any two vertices and does not contain loops,
        // meaning no edge connects a vertex to itself. In a simple graph,
        // the edges are undirected, allowing traversal in both directions
        // between connected vertices.

        // per constraint
        // n-1 <= edges.length <= 1e9
        // max edges length 1e9 ??? maybe typo ???

        vector<array<int,2>> G[50000];
        for(auto edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            G[u].push_back({v,w});
            G[v].push_back({u,w});
        }


        const long long INF = LLONG_MAX;

        // Dijkstra's algorithm

        // min heap
        // dist, node, excluded
        // priority_queue<array<long long,3>,vector<array<long long,3>>,greater<array<long long,3>>> pq;
        auto cmp = [](const array<long long,3>& a, const array<long long,3>& b){
            return a[0] > b[0];
        };
        priority_queue<array<long long,3>,vector<array<long long,3>>,decltype(cmp)> pq(cmp);


        // distances
        long long A[50000][2];
        for(int i = 0; i < n; ++i)
            A[i][0] = A[i][1] = INF;

        // push our source vertex into priority queue
        int s = 0;
        pq.push({0,s,0});
        // set distance to our source vertex itself to 0
        A[s][0] = 0;
        A[s][1] = 0;

        int u,v, excluded;
        long long dist, weight;
        while(!pq.empty()) {

            dist = pq.top()[0];
            u = pq.top()[1];
            // early exit if u == destination
            if( u == n-1 )
                return dist;

            excluded = pq.top()[2];
            pq.pop();

            // prune !!!
            if( A[u][excluded] < dist )
                continue;

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];

                //  If there is shorter path to v through u.
                if( A[v][excluded] > A[u][excluded] + weight ) {
                    // Updating distance of v
                    A[v][excluded] = A[u][excluded] + weight;
                    pq.push({A[v][excluded], v, excluded});
                }

                // if not yet excluded also try with excluding the current edge
                if( excluded == 0 ) {
                    if( A[v][1] > A[u][0] ) {
                        A[v][1] = A[u][0];
                        pq.push({A[v][1], v, 1});
                    }
                }
            }
        }

        // we should never get here
        return -1LL;
    }
};


// passes 914/921 test cases as of 12/18/2025 then TLE
// test case 915 also TLE locally


class Solution {
private:

    const long long INF = LLONG_MAX;

    // Dijkstra's algorithm
    long long shortestPath(int n, vector<array<int,2>> G[], int s, int d) {

        // min heap
        // dist, node, excluded
        priority_queue<array<long long,3>,vector<array<long long,3>>,greater<array<long long,3>>> pq;

        // distances
        // node: {{excluded, dist}, ...}
        vector<unordered_map<long long,long long>> A(n);

        // push our source vertex into priority queue
        pq.push({0,s,-1});
        // set distance to our source vertex itself to 0
        // A[s] = 0;

        int u,v;
        long long weight,excluded;
        while(!pq.empty()) {

            u = pq.top()[1];
            // TODO early exit if u == d
            if( u == d )
                return pq.top()[0];

            excluded = pq.top()[2];
            pq.pop();

            // A[u]
            long long Au = INF;
            if( u == 0 ) {
                Au = 0;
            } else {
                auto f = A[u].find(excluded);
                if( f != A[u].end() )
                    Au = f->second;
            }

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                if( v == s ) // we are not going back to source
                    continue;

                weight = (*it)[1];

                if( excluded != -1 && weight > excluded )
                    continue;

                // A[v]
                long long Av = INF;
                auto f = A[v].find(excluded);
                if( f != A[v].end() )
                    Av = f->second;

                //  If there is shorter path to v through u.
                if( Av > Au + weight ) {
                    // Updating distance of v
                    //A[v] = A[u] + weight;
                    auto p = A[v].insert({excluded, Au + weight});
                    if( !p.second )
                        p.first->second = Au + weight;

                    pq.push({Au + weight, v, excluded});
                }

                // TODO if not yet excluded also try with excluding the current edge
                if( excluded == -1 ) {
                    if( Av > Au ) {
                        // Updating distance of v
                        //A[v] = A[u] + weight;
                        auto p = A[v].insert({weight, Au});
                        if( !p.second )
                            p.first->second = Au;

                        pq.push({Au, v, weight});
                    }
                }

            }
        }

        // should never get here
        long long ret = INF;
        for(auto p: A[d])
            ret = min(ret, p.second);

        return ret; //A[d];
    }

public:
    long long minCostExcludingMax(int n, vector<vector<int>>& edges) {
        // 1 <= n <= 50000
        // edges[i] = [ui, vi, wi]
        // 1 <= wi <= 50000 ??? this is not reality, test case 913 uses greater values
        // weighted connected simple undirected graph
        // A simple graph is a type of graph that does not have multiple
        // edges between any two vertices and does not contain loops,
        // meaning no edge connects a vertex to itself. In a simple graph,
        // the edges are undirected, allowing traversal in both directions
        // between connected vertices.

        // per constraint
        // n-1 <= edges.length <= 1e9
        // max edges length 1e9 ??? maybe typo ???

        vector<array<int,2>> G[50000];
        for(auto edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            G[u].push_back({v,w});
            G[v].push_back({u,w});
        }

        return shortestPath(n, G, 0, n-1);
    }
};
