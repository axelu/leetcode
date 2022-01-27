
// 815. Bus Routes
// https://leetcode.com/problems/bus-routes/




class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if( source == target )
            return 0;

        struct Bus {
            int nbr;
            int stopEntered; // node entered for cycle detection
            int currStop;    // current node
            int bussesTaken;
        };

        vector<array<int,2>> g[1000000]; // node,bus

        // directed graph with edge indicating the bus nbr serving that edge
        // bus routes to graph
        // int mnStop = INT_MAX, mxStop = INT_MIN;
        for(int i = 0; i < routes.size(); ++i) {        // bus number
            int n   = routes[i].size();  // do we even need to consider a bus with 1 stop?
                                         // constraint given: 1 <= routes[i].length <= 10^5
            for(int j = 1; j < n; ++j) {                // stop number aka node number
                // cout << "adding src " << routes[i][j-1] << " dest " << routes[i][j] << " bus nbr " << i << endl;
                g[routes[i][j-1]].push_back({routes[i][j],i});
            }
            // close the bus loop
            // cout << "adding src " << routes[i][n-1] << " dest " << routes[i][0] << " bus nbr " << i << endl;
            g[routes[i][n-1]].push_back({routes[i][0],i});
        }




        // BFS
        // min heap to minimize the number of busses taken
        auto cmp = [](const Bus& a, const Bus& b){
            return a.bussesTaken > b.bussesTaken;
        };
        priority_queue<Bus,vector<Bus>,decltype(cmp)> pq(cmp);
        int seen[500];memset(seen,0,sizeof seen); // are we already on that bus
        // depart from source in all busses leaving from source
        for(int i = 0; i < g[source].size(); ++i) {
            // cout << "leaving src " << source << " on bus nbr " << g[source][i][1];
            // cout << " next stop " << g[source][i][0] << endl;
            pq.push({g[source][i][1],source,g[source][i][0],1});
            seen[g[source][i][1]] = 1;
        }
        // cout << "pq size initially " << pq.size() << endl;

        Bus bus;
        while(!pq.empty()) {
            // cout << "pq size begin " << pq.size() << endl;
            bus = pq.top();
            pq.pop();
            // cout << "pq size begin after pop " << pq.size() << endl;

            /*
            cout << "bus nbr " << bus.nbr;
            cout << " entered at stop " << bus.stopEntered;
            cout << " current stop " << bus.currStop;
            cout << " busses taken " << bus.bussesTaken << endl;
            */

            if( bus.currStop == target )
                return bus.bussesTaken;

            // if the current stop is the stop we entered,
            // then there is no point in continuing on this bus
            // if( bus.currStop == bus.stopEntered ) {
            //     cout << "bus " << bus.nbr << " made a complete circle " << endl;
            //     continue;
            // }

            // cout << "before checking transfer options and continue options" << endl;
            // cout << "number of departing busses including ours " << g[bus.currStop].size() << endl;
            for(int i = 0; i < g[bus.currStop].size(); ++i) {

                // is this is our current bus? keep going, unless the next stop is the stop we entered
                if( g[bus.currStop][i][1] == bus.nbr ) {
                    if( bus.stopEntered != g[bus.currStop][i][0] ) {
                        // cout << "continue on our current bus " << bus.nbr << " to its next stop " << g[bus.currStop][i][0] << endl;
                        pq.push({bus.nbr,bus.stopEntered,g[bus.currStop][i][0],bus.bussesTaken});
                    }
                    continue;
                }

                // are we already on this bus?
                if( seen[g[bus.currStop][i][1]] )
                    continue;

                // transfer onto next bus
                pq.push({g[bus.currStop][i][1],bus.currStop,g[bus.currStop][i][0],bus.bussesTaken+1});
                seen[g[bus.currStop][i][1]] = 1;
            }
        }
        return -1;
    }
};
