
// 1870. Minimum Speed to Arrive on Time
// https://leetcode.com/problems/minimum-speed-to-arrive-on-time/



class Solution {
private:
    int n; // number of trains

    double calcArrival(vector<int>& dist, int speed) {
        // calculate the arrival if traveling at speed speed

        double arrival = 0.0;
        for(int i = 0; i < n-1; ++i)
            arrival += ceil((double)dist[i]/speed);

        // last train
        arrival += (double)dist.back()/speed;

        return arrival;
    }

    // binary search
    int search(vector<int>& dist, int s, int e, double hour) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        double arrival = calcArrival(dist,mid);
        if( arrival <= hour ) {
            // can we do better? meaning: can we can go slower?
            int t = search(dist,s,mid-1,hour);
            return t != -1 ? t : mid;
        } else {
            // we need to go faster
            return search(dist,mid+1,e,hour);
        }
    }

public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        n = dist.size();

        if( n == 1 )
            return ceil( (double)dist[0]/hour - 1e-9 );


        // can we make it at all?
        // every train except the last has to wait for the full hour
        // with that the minimum travel time is n-1
        if( (double)(n-1) >= hour )
            return -1;

        int  maxDist = 0;
        for(int i = 0; i < n; ++i)
            maxDist = max(maxDist,dist[i]);

        // cutoff speed = any speeds larger will always allow to arrive on time
        // the larger of
        // speed needed to make all trains except the last ride in under an hour or exactly in one hour
        // speed needed to make last train cover the last distance in the remaining time
        int e = max(maxDist,(int)ceil(dist.back()/(hour-(n-1))));

        return search(dist,0,e,hour);
    }
};
