
// 3112. Minimum Time to Visit Disappearing Nodes
// https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/




class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        // disappear.length == n

        int u,v,weight;

        // the graph may have duplicate edges, we only keep the smallest edge between 2 nodes
        unordered_map<int,int> G[n];
        for(auto& edge: edges) {
            u = edge[0];
            v = edge[1];
            weight = edge[2];

            //if( weight >= disappear[u] || weight >= disappear[v] )
            //    continue;

            auto p = G[u].insert({v,weight});
            if( !p.second ) {
                G[u][v] = min(G[u][v], weight);
                G[v][u] = min(G[v][u], weight);
            } else {
                G[v].insert({u,weight});
            }
        }

        // Dijkstra's algorithm shortestPath
        // min heap
        multimap<int,int> pq;
        multimap<int,int>::iterator pq_it;

        // keep track of what is in our min heap by node
        unordered_map<int, multimap<int,int>::iterator> pq_dic;

        // distances
        vector<int> A(n,1000000000);

        // push our source vertex into priority queue
        pq_it = pq.insert({0,0});
        pq_dic.insert({0, pq_it});

        // set distance to our source vertex itself to 0
        A[0] = 0;

        while( !pq.empty() ) {
            u = pq.begin()->second;
            pq.erase(pq.begin());
            pq_dic.erase(u);

            for(auto it = G[u].begin(); it != G[u].end(); ++it) {
                v = it->first;
                weight = it->second;

                //  If there is shorter path to v through u?
                if( A[u] + weight < disappear[v] && A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;

                    auto f = pq_dic.find(v);
                    if( f != pq_dic.end() ) {
                        pq.erase(f->second);
                        pq_dic.erase(f);
                    }
                    auto pq_it = pq.insert({A[v], v});
                    pq_dic.insert({v,pq_it});
                }
            }
        }

        for(int i = 0; i < n; ++i)
            if( A[i] == 1000000000 )
                A[i] = -1;

        return A;
    }
};
