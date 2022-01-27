
// 882. Reachable Nodes In Subdivided Graph
// https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/
//
// NOTE: not final solution, this one TLE on case 43/47, meaning it passes 42 cases






class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        if( maxMoves == 0 )
            return 1;

        // n nodes labeled from 0 to n-1
        int i;

        // undirected graph
        vector<array<int,2>> G[n];
        map<array<int,2>,int> mp;
        for(i = 0; i < edges.size(); ++i) {
            G[edges[i][0]].push_back({edges[i][1],edges[i][2]+1});
            mp.insert({{edges[i][0],edges[i][1]},edges[i][2]});
            G[edges[i][1]].push_back({edges[i][0],edges[i][2]+1});
            mp.insert({{edges[i][1],edges[i][0]},edges[i][2]});
        }


        // Dijkstra's algorithm
        // shortest path

        // min heap
        priority_queue<array<long,2>,vector<array<long,2>>,greater<array<long,2>>> pq;


        long A[n+1];    // distances
        int prev[n+1];  // predecessor
        for(int i = 0; i < n+1; ++i) {
            A[i] = LONG_MAX;
            prev[i] = -1;
        }

        // push our source vertex into priority queue
        int s = 0; // we are starting from vertex 0
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v;
        long weight;
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
                    // Update predecessor of v
                    prev[v] = u;
                }
            }
        }



        int seen[n+1];memset(seen,0,sizeof seen);
        int ans = 1; // vertex 0
        seen[0] = 1;

        set<array<int,2>>    complete;  // edges traversed completely
        map<array<int,2>,int> partial;  // edges traversed partially


        for(v = 0; v <= n; ++v) {
           if( A[v] <= (long)maxMoves )  {
               // we were able to reach node v in the original graph
               // cout << "reached node v " << v << " at distance " << A[v] << " from node 0" << endl;

               // add node v to answer
               if( !seen[v] ) {
                   ++ans;
                   seen[v] = 1;
               }

               // fully consumed edges
               // all edges traversed from node 0 to node v have been fully consumed
               int tv = v;          // temp v
               int tu = prev[tv];   // temp u
               while( tu != -1 ) {
                   // cout << "  came to " << tv << " via " << tu << endl;
                   // add node u to answer
                    if( !seen[tu] ) {
                        ++ans;
                        seen[tu] = 1;
                    }

                   // edge u -> v
                   if( !complete.count({tu,tv}) ) {
                       // remove from partial edges if applicable
                       partial.erase({tu,tv});
                       partial.erase({tv,tu});
                       // count nodes
                       ans += mp.find({tu,tv})->second;
                       // add to complete traversed edges
                       complete.insert({tu,tv});
                       complete.insert({tv,tu});
                   }

                   // edge v -> u
                   // already covered
                   tv = tu;
                   tu = prev[tv];
               }

               // cout << "  ans " << ans << endl;

               // partial edges
               // how much further can we go from node v? -> partial edges
               long d = (long)maxMoves - A[v];
               if( d > 0 ) {
                    // cout << "  have " << d << " move(s) left" << endl;
                    vector<array<int,2>>::iterator it;
                    for(it = G[v].begin(); it != G[v].end(); ++it) {
                        u = (*it)[0];

                        if( complete.count({u,v}) )
                            continue;

                        // cout << "  partial edge from v " << v << " to " << u << endl;

                        auto f = partial.find({v,u});
                        if( f != partial.end() ) {
                            f->second = max((int)d,f->second);
                        } else {
                            partial.insert({{v,u},d});
                        }
                    }
               }
           }
        }
        /*
        // we would not have covered any partial edges starting from node 0
        vector<array<int,2>>::iterator it;
        for(it = G[0].begin(); it != G[0].end(); ++it) {
            u = (*it)[0];
            weight = (*it)[1];
            if( weight > maxMoves ) {
                cout << "adding partial edge from node 0 to " << u << endl;
                partial.insert({{0,u},maxMoves});
            }
        }
        */

        // process partial edges
        // cases: edge only in partial in one direction
        //        edge in partial from both directions non-overlapping
        //        edge in partial from both directions overlapping
        map<array<int,2>,int>::iterator pit;
        for(auto pit = partial.begin(); pit != partial.end(); ++pit) {
            u = pit->first[0];
            v = pit->first[1];

            // cout << "processing partial edge u " << u << " v " << v << endl;

            weight = mp.find({u,v})->second;
            auto f = partial.find({v,u});
            if( f == partial.end() ) {
                // cout << "  adding " << min(pit->second,(int)weight) << " nodes" << endl;
                ans += min(pit->second,(int)weight);
                continue;
            }

            if( distance(f,partial.end()) > distance(pit,partial.end()) )
                continue;

            // cout << "  adding " << min(pit->second + f->second,(int)weight) << " nodes" << endl;
            ans += min(pit->second + f->second,(int)weight);
        }

        return ans;
    }
};
