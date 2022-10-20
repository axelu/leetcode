
// 2361. Minimum Costs Using the Train Line
// https://leetcode.com/problems/minimum-costs-using-the-train-line/




class Solution {
public:
    vector<long long> minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {
        int n = regular.size(); // regular.length == express.length


        vector<array<int,2>> g[2*n+2];

        // build graph for regular line
        // including the transfer to the express line
        for(int i = 0; i < n; ++i) {
            // regular line
            g[i].push_back({i+1,regular[i]});
            // transfer from regular line to express line
            g[i].push_back({i+1+n,expressCost});
            // express line
            g[i+1+n].push_back({i+1+n+1,express[i]});
            // transfer from express line to regular line
            if( i > 0 )
                g[i+1+n].push_back({i,0});
        }

        // Dijkstra's algorithm

        // min heap
        priority_queue<array<long,2>,vector<array<long,2>>,greater<array<long,2>>> pq;

        // distances
        long A[2*n+2];
        for(int i = 0; i < 2*n+2; ++i)
            A[i] = 10000000001;

        // push our source vertex into priority queue
        pq.push({0,0});
        // set distance to our source vertex itself to 0
        A[0] = 0;

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = g[u].begin(); it != g[u].end(); ++it) {
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

        vector<long long> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = min(A[i+1],A[i+1+n+1]);

        return ans;
    }
};
