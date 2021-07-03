
// 871. Minimum Number of Refueling Stops
// https://leetcode.com/problems/minimum-number-of-refueling-stops/


class Solution {    
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // can we reach the target w/o any stop?
        if( startFuel >= target ) return 0;
        
        int n = stations.size();
        if( n == 0 ) return -1; // not enough start fuel and there are no stations

        
        // pq is a maxheap of gas station capacities
        priority_queue<int> pq;
        int ans = 0,prev = 0;
        int tank = startFuel;
        for(int i = 0; i < n; ++i) {
            int location = stations[i][0];
            int capacity = stations[i][1];
            tank -= location - prev;
            while(!pq.empty() && tank < 0) {  // must refuel in past
                tank += pq.top();
                pq.pop();
                ans++;
            }

            if( tank < 0 ) return -1;
            pq.push(capacity);
            prev = location;
        }


        // Repeat body for station = (target, inf)
        {
            tank -= target - prev;
            while (!pq.empty() && tank < 0) {
                tank += pq.top();
                pq.pop();
                ans++;
            }
            if (tank < 0) return -1;
        }

        return ans;

    }
};
