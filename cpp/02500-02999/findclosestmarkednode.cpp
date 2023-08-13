
// 2737. Find the Closest Marked Node
// https://leetcode.com/problems/find-the-closest-marked-node/



class Solution {
private:
    // Dijkstra's algorithm
    vector<int> shortestPath(int n, unordered_map<int,int> G[], int s) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        vector<int> A(n,INT_MAX);

        // push our source vertex into priority queue
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            for(auto it = G[u].begin(); it != G[u].end(); ++it) {
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

        return A;
    }

public:
    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {
        // the graph might have repeated edges, so we only keep the shortest to begin with

        unordered_map<int,int> G[n]; // directed graph
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            auto p = G[u].insert({v,weight});
            if( !p.second && p.first->second > weight )
                p.first->second = weight;
        }

        vector<int> distances = shortestPath(n,G,s);

        int ans = INT_MAX;
        for(int i = 0; i < marked.size(); ++i) {
            ans = min(ans,distances[marked[i]]);
        }

        return ans != INT_MAX ? ans : -1;
    }
};
