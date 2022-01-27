
// 853. Car Fleet
// https://leetcode.com/problems/car-fleet/




class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size(); // position.size() = speed.size()
        if( n < 2 ) return n;

        map<int,int> m; // distance to target,speed
        for(int i = 0; i < n; ++i)
            m.insert({target-position[i],speed[i]});

        int ans = n;
        map<int,int>::iterator it = m.begin();
        double prevCarArrivalTime = (double)it->first/(double)it->second;
        double currCarArrivalTime;
        for(it = next(it); it != m.end(); ++it) {
            // if we catch up to the car in front of us
            // we become part of 'its' fleet
            currCarArrivalTime = (double)it->first/(double)it->second;

            if( currCarArrivalTime > prevCarArrivalTime + 1e-9 ) {
                // current car does NOT catch up to car in front of it
                prevCarArrivalTime = currCarArrivalTime;
            } else {
                // current car does catch up to car in front of it
                // and with that becomes part of its fleet
                --ans;
            }
        }

        return ans;
    }
};
