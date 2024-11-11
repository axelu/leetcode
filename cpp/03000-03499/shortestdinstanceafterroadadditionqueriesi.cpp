
// 3243. Shortest Distance After Road Addition Queries I
// https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/






class Solution {
private:
    int * A;

    // Dijkstra's algorithm
    void shortestPath(int n, vector<int> G[], int s) {
        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // push our source vertex into priority queue
        pq.push({A[s],s});

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            vector<int>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it);
                weight = 1;

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        return;
    }

public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        int q_sz = queries.size();

        // build a  unidirectional graph
        vector<int> g[n];
        for(int i = 0; i < n-1; ++i)
            g[i].push_back(i+1);

        A = new int[n];
        for(int i = 0; i < n; ++i)
            A[i] = i;

        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            // adding a new road from a to b
            int a = queries[i][0];
            int b = queries[i][1];

            g[a].push_back(b);

            shortestPath(n, g, a);

            ans[i] = A[n-1];
        }

        return ans;
    }
};
