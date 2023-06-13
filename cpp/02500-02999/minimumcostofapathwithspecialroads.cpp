
// 2662. Minimum Cost of a Path With Special Roads
// https://leetcode.com/problems/minimum-cost-of-a-path-with-special-roads/


class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        if( start == target )
            return 0;
        
        // we need to build a complete bidirectional graph
        // a complete graph means that every vertex is connected with every other vertex.
        // number of edges: n * (n-1) / 2
        // worst case
        // start, target, and specialRoads.size() == 200 and each is different
        // -> n = 402 -> edges 80601
        
        unordered_map<long,int> um; // (x << 17) + y, nodeid
        unordered_map<int,pair<int,int>> nodes;
        int nodeid = 0;
        // start nodeid 0
        long t = ((long)start[0] << 17) + start[1];
        um[t] = nodeid;
        nodes[nodeid] = {start[0],start[1]};
        ++nodeid;
        
        // target nodeid 1
        t = ((long)target[0] << 17) + target[1];
        um[t] = nodeid;
        nodes[nodeid] = {target[0],target[1]};
        ++nodeid;
        
        long ul,vl; 
        for(auto& road: specialRoads) {
            ul = ((long)road[0] << 17) + road[1];
            vl = ((long)road[2] << 17) + road[3];
            if( ul == vl )
                continue;
        
            auto p = um.insert({ul,nodeid});
            if( p.second ) {
                nodes[nodeid] = {road[0],road[1]};
                ++nodeid;
            }
            p = um.insert({vl,nodeid});
            if( p.second ) {
                nodes[nodeid] = {road[2],road[3]};
                ++nodeid;
            }
        }
        
        // number of unique nodes
        int n = um.size();
        
        int adj[n][n];memset(adj,-1,sizeof adj);
        // we should set adj[i][i] = 0 for 0 <= i < n
        
        // start to end bidirectional manhattan distance
        int cost = abs(target[0] - start[0]) + abs(target[1] - start[1]);
        adj[0][1] = cost;
        adj[1][0] = cost;
        
        for(auto& road: specialRoads) {
            ul = ((long)road[0] << 17) + road[1];
            vl = ((long)road[2] << 17) + road[3];
            if( ul == vl )
                continue;
        
            int u_idx = um[ul];
            int v_idx = um[vl];
            
            // manhattan distance
            cost = abs(road[2] - road[0]) + abs(road[3] - road[1]);
        
            // special road
            int special = road[4];
            
            // special road maybe longer than manhattan distance, 
            // or maybe we already have a better special road
            int mn;
            if( adj[u_idx][v_idx] != -1 )
                mn = min({adj[u_idx][v_idx],cost,special});
            else
                mn = min(cost,special);
            
            adj[u_idx][v_idx] = mn;   // special roads are directional!
            
            if( adj[v_idx][u_idx] != -1 )
                cost = min(adj[v_idx][u_idx],cost);
            adj[v_idx][u_idx] = cost; // special roads are directional!
        }
        
        // go through all again and add edge if not yet done
        int u,v;
        for(u = 1; u < n; ++u) {
            for(v = 0; v < u; ++v) {
                auto pu = nodes[u];
                auto pv = nodes[v];
                cost = abs(pv.first - pu.first) + abs(pv.second - pu.second);
                if( adj[u][v] == -1 )
                    adj[u][v] = cost;
                if( adj[v][u] == -1 )
                    adj[v][u] = cost;
                
            }
        }
           
        // Dijkstra's algorithm shortest path on a complete graph
        // s is node with nodeid 0
        // target is node with nodeid 1
        
        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        vector<int> A(n,INT_MAX);

        // push our source vertex into priority queue
        pq.push({0,0});
        // set distance to our source vertex itself to 0
        A[0] = 0;

        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            for(v = 0; v < n; ++v) {
                if( v == u )
                    continue;
                
                cost = adj[u][v];

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + cost ) {
                    // Updating distance of v
                    A[v] = A[u] + cost;
                    pq.push({A[v], v});
                }
            }
        }
        
        return A[1];
    }
};
