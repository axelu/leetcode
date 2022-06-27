
// 2039. The Time When the Network Becomes Idle
// https://leetcode.com/problems/the-time-when-the-network-becomes-idle/


class Solution {
private:

public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        // if we calculate the shortest path from master server node 0
        // to each server, then we know how long it will take for each server
        // to receive the answer to the 1st message -> shortest path * 2
        // while waiting each server may send out more messages at
        // patience interval and only stops, when the answer to the 1st msg
        // was received, so we need to wait for the last msg emitted to
        // return -> (shortest path * 2 ) / patience + (shortest path * 2 )
        // do this for all nodes and the max is our answer

        int n = patience.size();

        // bidirectional graph
        vector<int> g[n];
        for(auto& edge : edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        // BFS

        int A[n]; // shortest distance from node 0 (master server) to node i
        memset(A,-1,sizeof A);
        queue<int> q;
        q.push(0);
        A[0] = 0;
        int step = 1;
        while( !q.empty() ) {
            queue<int> q_new;
            while( !q.empty() ) {
                int u = q.front();
                q.pop();

                for(int v : g[u] )
                    if( A[v] == -1 ) {
                        q_new.push(v);
                        A[v] = step;
                    }
            }
            q = q_new;
            ++step;
        }

        int ans = 0;
        for(int i = 1; i < n; ++i) {
            // travel time of msg from server i to 0 to i
            int t = A[i]*2;
            // the second after that would be the earliest the network is quiet
            int a = t + 1;

            // but we may have sent msg while waiting
            int s = t % patience[i] == 0 ? (t/patience[i] - 1) * patience[i] : (t/patience[i]) * patience[i];
            a = max(a, s + t + 1);

            ans = max(ans,a);
        }

        return ans;
    }
};
