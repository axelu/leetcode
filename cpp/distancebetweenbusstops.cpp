
// 1184. Distance Between Bus Stops
// https://leetcode.com/problems/distance-between-bus-stops/

class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        if( start == destination ) return 0;
        int t = accumulate(begin(distance),end(distance),0);
        int s,e;
        if( start < destination ) {
            s = start;
            e = destination;
        } else {
            s = destination;
            e = start;
        }

        int a = 0;
        for(int i = s; i < e; ++i)
            a += distance[i];
        int b = t - a;

        return min(a,b);
    }
};
