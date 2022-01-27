
// 743. Network Delay Time
// https://leetcode.com/problems/network-delay-time/



class Solution {
private:

    // Dijkstra's algorithm
    void shortestPath(int n, vector<array<int,2>> G[], int s, int A[]) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // push our source vertex into priority queue
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];

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
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // n network nodes numbered from 1 to n
        int i;

        // directed weigthed graph
        vector<array<int,2>> g[n+1];
        for(i = 0; i < times.size(); ++i)
            g[times[i][0]].push_back({times[i][1],times[i][2]});

        // distances
        int A[n+1];
        for(i = 1; i < n+1; ++i) A[i] = 1000000;

        int ans = 0;

        shortestPath(n,g,k,A);
        for(i = 1; i < n+1; ++i) {
            if( A[i] == 1000000 )
                return -1;
            ans = max(ans,A[i]);
        }
        return ans;
    }
};
