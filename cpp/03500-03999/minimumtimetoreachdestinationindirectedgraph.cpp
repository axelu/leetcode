
// 3604. Minimum Time to Reach Destination in Directed Graph
// https://leetcode.com/problems/minimum-time-to-reach-destination-in-directed-graph/



class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        // directed graph

        vector<vector<vector<int>>> g(n);
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int start = edge[2];
            int end = edge[3];

            g[u].push_back({v, start, end});
        }

        // BFS
        vector<int> A(n, INT_MAX);

        // {arrival time, node}
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            return a[0] > b[0];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

        pq.push({0, 0});
        A[0] = 0L;
        while( !pq.empty() ) {
            int arrival_time = pq.top()[0];
            int u = pq.top()[1];
            pq.pop();

            if( u == n-1 )
                return arrival_time;

            for(int i = 0; i < g[u].size(); ++i) {
                int v = g[u][i][0];
                int start = g[u][i][1];
                int end = g[u][i][2];

                if( arrival_time > end )
                    continue;

                if( arrival_time > start )
                    start = arrival_time;

                // travel takes 1 time unit
                ++start;

                if( A[v] <= start )
                    continue;

                A[v] = start;
                pq.push({start, v});
            }
        }

        return -1;
    }
};
