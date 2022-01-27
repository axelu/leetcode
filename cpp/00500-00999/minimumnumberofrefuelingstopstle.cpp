
// 871. Minimum Number of Refueling Stops
// https://leetcode.com/problems/minimum-number-of-refueling-stops/

// not final solution, passes 138/198 tests, but ends in TLE
// delivers correct results though




class Solution {
private:

    int rec(vector<vector<int>>& stations, int n, int currStation, int remainingFuel, int target) {
        // returns the number of refuelStops it took to reach
        // the target from the current station or
        // -1 if the target could not be reached


        // Can we reach the target w/o refueling?
        if( currStation == -1 ) { // we are at start
            if( target <= remainingFuel )
                return 0;
        } else {
            if( target-stations[currStation][0] <= remainingFuel )
                return 0;
        }

        // we have the choice:
        // go to all stations we can reach from here w/o refueling and
        // go to all stations we can reach from here w/ refueling

        // Can we reach the target w/ refueling?
        if( currStation != -1 && target-stations[currStation][0] <= remainingFuel+stations[currStation][1] )
            return 1;

        int ret = INT_MAX;
        int stops;
        int currPos = currStation == -1 ? 0 : stations[currStation][0];

        // Go to all stations we can reach w/o refueling
        int i = currStation+1;
        while( i < n && stations[i][0]-currPos <= remainingFuel ) {
            stops = rec(stations,n,i,remainingFuel-(stations[i][0]-currPos),target);
            if( stops != -1 )
                ret = min(ret,stops);
            ++i;
        }
        // Go to all stations we can reach w/ refueling
        if( currStation != -1 ) {
            i = currStation+1;
            while( i < n && stations[i][0]-currPos <= remainingFuel+stations[currStation][1] ) {
                stops = rec(stations,n,i,remainingFuel+stations[currStation][1]-(stations[i][0]-stations[currStation][0]),target);
                if( stops != -1 )
                    ret = min(ret,stops+1);
                ++i;
            }
        }

        return ret == INT_MAX ? -1 : ret;
    }

public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // can we reach the target w/o any stop?
        if( startFuel >= target ) return 0;

        int n = stations.size();
        if( n == 0 ) return -1; // not enough start fuel and there are no stations

        // TODO mem
        // return rec(stations,n,-1,startFuel,target);


        vector<vector<long>> g[n+2]; // directed weigthed graph
        int pos = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = i; j < n; ++j) {
                g[i].push_back({j+1,stations[j][0]-pos,stations[j][1]});
            }
            g[i].push_back({n+1,target-pos,INT_MAX});
            pos = stations[i][0];
        }
        g[n].push_back({n+1,target-pos,INT_MAX});

        // debug
        /*
        for(int i = 0; i < n+2; ++i) {
            cout << "i " << i << endl;
            for(int j = 0; j < g[i].size(); ++j) {
                cout << g[i][j][0] << " " << g[i][j][1] << " " << g[i][j][2] << endl;
            }
        }
        */


        // least number stops, most remaining fuel
        auto cmp = [](const array<long,3>& a, const array<long,3>& b) {
            if( a[2] > b[2] ) {         // number of stops
                return true;
            } else if( a[2] == b[2] ) {
                return a[1] < b[1];     // remaining fuel
            }
            return false;
        };
        priority_queue<array<long,3>,vector<array<long,3>>,decltype(cmp)> pq(cmp);

        // BFS
        queue<array<long,3>> q;  // node,remainingfuel,stops
        long dest = n+1;         // destination node
        pq.push({0,startFuel,0});

        unordered_set<long> seen;


        long u,remainingFuel,stops,v;
        while(!pq.empty()) {
            u             = pq.top()[0];
            remainingFuel = pq.top()[1];
            stops         = pq.top()[2];
            pq.pop();

            //cout << "u " << u << " rF " << remainingFuel << " stops " << stops << endl;

            long t = (unsigned long)u << 55;
            t += (unsigned long)remainingFuel << 16;
            //t += (unsigned long)stops;

            if( !seen.count(t) ) {
                seen.insert(t);

                 // collect and prioritize
                for(int i = g[u].size()-1; i >= 0; --i) {
                    v = g[u][i][0];
                    // can we make it to v w/o refueling?
                    if( remainingFuel >= g[u][i][1] ) {
                        if( v == dest ) return stops;
                        pq.push({v,remainingFuel-g[u][i][1],stops});
                    }
                    // can we make it to v w/ refueling?
                    if( u != 0 && remainingFuel+stations[u-1][1] >= g[u][i][1] ) {
                        if( v == dest ) return stops+1;
                        pq.push({v,remainingFuel+stations[u-1][1]-g[u][i][1],stops+1});
                    }
                }

            }
            /*
            if(q.empty()) {
                while(!pq.empty()) {
                    q.push(pq.top());
                    pq.pop();
                }
            }
            */
        }
        return -1;
    }
};
