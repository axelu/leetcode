
// 2203. Minimum Weighted Subgraph With the Required Paths
// https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/




class Solution {
private:
    // Dijkstra's algorithm
    void shortestPath(int n, unordered_map<int,int> G[], int s, long A[]) {

        // min heap
        auto cmp = [](const pair<long,int>& a, const pair<long,int>& b) {
            return a.first > b.first;
        };
        priority_queue<pair<long,int>,vector<pair<long,int>>,decltype(cmp)> pq(cmp);

        // push our source vertex into priority queue
        pq.push({0L,s});
        // set distance to our source vertex itself to 0
        A[s] = 0L;

        int u,v;
        long weight;
        while(!pq.empty()) {

            u = pq.top().second;
            pq.pop();

            unordered_map<int,int>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = it->first;
                weight = it->second;

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }
    }

public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        // rephrasing the question
        //     - there has to be a path from scr1 to dest
        //     - there has to be a path from src2 to dest
        //     - if one of them does not have a path, then there is no solution
        //
        // possible subgraphs:
        //     src1 -> src2 -> dest
        //     src2 -> src1 -> dest
        // if neither src1 nor src2 have a path to dest, then there is no solution
        // otherwise ans: min(src1->dest + src2->dest, src1->src2 + src2->dest, src2->src1 + src1->dest)
        // if we run Dijkstra from src1->dest and src2->dest we can answer it.

        // now there additionally there can be a graph such as this:
        // n = 4
        // [[0,2,1],[2,3,1],[1,2,1]]
        // src1 = 0
        // src2 = 1
        // dest = 3
        // ans = 3: 1->2,0->2,2->3
        // meaning the path from src1 and src2 converge on some node and form the shortest subgraph
        // which would require to know shortest path from all nodes to dest :-(
        // like
        //         for(int i = 0; i < n; ++i) {
        //            if( i != src1 && i != src2 && i != dest ) {
        //                t = min(t, A[i] + B[i] + I[dest]); // TODO that requires shortest path all nodes to dest

        // but if we flip the directions of the edges, we have the answer
        // by just going from dest to all nodes

        // Note: there are duplicate edges.

        // directed weigthed graph reversed
        unordered_map<int,int> gr[n];
        for(int i = 0; i < edges.size(); ++i) {
            auto p = gr[edges[i][1]].insert({edges[i][0],edges[i][2]});
            if( !p.second )
                p.first->second = min(p.first->second,edges[i][2]);
        }

        long A[n]; // src: dest
        for(int i = 0; i < n; ++i)
            A[i] = 10000000001;

        shortestPath(n,gr,dest,A);
        if( A[src1] == 10000000001 || A[src2] == 10000000001 )
            return -1;

        // directed weigthed graph
        unordered_map<int,int> g[n];
        for(int i = 0; i < edges.size(); ++i) {
            auto p = g[edges[i][0]].insert({edges[i][1],edges[i][2]});
            if( !p.second )
                p.first->second = min(p.first->second,edges[i][2]);
        }

        long B[n]; // src: src1
        long C[n]; // src: src2
        for(int i = 0; i < n; ++i)
            B[i] = C[i] = 10000000001;

        shortestPath(n,g,src1,B);
        shortestPath(n,g,src2,C);

        long t = min({B[dest]+C[dest], A[src2]+B[src2], A[src1]+C[src1]});
        if( t >= 10000000001 )
            return -1;

        for(int i = 0; i < n; ++i)
            if( i != src1 && i != src2 && i != dest )
                t = min(t, A[i] + B[i] + C[i]);

        return t;
    }
};
