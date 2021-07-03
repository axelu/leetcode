
// 1883. Minimum Skips to Arrive at Meeting On Time
// https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/




class Solution {
private:
    int n; // number of roads
    double o = 1e-9;
    int ans;

    double mem[1001][1001];

    void rec(vector<double>& travelTimes, int road, double currentTime, int skips, int& hoursBefore) {
        // cout << setprecision(20);
        // cout << "rec road " << road << " skips " << skips << " currentTime " << currentTime << endl;

        // there is no point in continuing if we are too late already
        if( abs(currentTime-(double)hoursBefore) > o && currentTime > (double)hoursBefore ) {
            // cout << setprecision(20);
            // cout << "too late road " << road << " skips " << skips << " currentTime " << currentTime << endl;
            // if( skips == travelTimes.size() ) // no skips and we are already too late -> we can never make it
            //    ans = -1;
            return;

        }

        // there is no point in continuing if there already is a better answer
        if( skips >= ans )
            return;


        // we arrived at the meeting
        if( road >= n ) {
            // cout << "arrived" << endl;
            ans = min(ans,skips);
            return;
        }


        // there is no point in continuing if we arrived at the same road and
        // equal number of skips at a better start time
        if( mem[road][skips] != -1 ) {
            if( abs(currentTime-mem[road][skips]) < o || currentTime > mem[road][skips] ) {
                // cout << "hit" << endl;
                return;
            }
        }
        mem[road][skips] = currentTime;


        // we have a choice:
        //     we rest before continuing OR
        //     at the start of each road, we continue without resting

        // continue without resting
        double startTimeWithoutRest = currentTime+travelTimes[road];
        rec(travelTimes,road+1,startTimeWithoutRest,skips+1,hoursBefore);

        // continue after resting
        // ceil(1.000000001) will equate to 2
        // we need 1.000000001 to be = 1 and not 2, hence ceil(1.000000001 - 0.00000001) to make it ceil to 1
        rec(travelTimes,road+1,ceil(startTimeWithoutRest-o),skips,hoursBefore);


    }

public:
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        n = dist.size(); // 1 <= n <= 1000
        // cout << "n " << n << endl;

        // pre-process travelTimes
        double travelTime;
        double minTraveltime = 0.0; // time to reach meeting to skip all rests
        vector<double> travelTimes(n);
        for(int i = 0; i < n; ++i) {
            travelTime = (double)dist[i]/speed;
            travelTimes[i] = travelTime;
            minTraveltime += travelTime;
            //cout << setprecision(20);
            //cout << "road " << i << " travelTime " << travelTimes[i] << " total Travel time " << minTraveltime << endl;
        }


        // could we even make it skipping all rests?
        // cout << setprecision(20);
        // cout << "minTraveltime skipping all rests " << minTraveltime << endl;
        if( abs(minTraveltime-(double)hoursBefore) > o && minTraveltime > (double)hoursBefore)
            return -1;


        for(int i = 0; i < 1001; ++i)
            for(int j = 0; j < 1001; ++j)
                mem[i][j] = -1;

        ans = 1002;
        double startTime = 0.0;
        rec(travelTimes,0,startTime,0,hoursBefore);

        return ans == 1002 ? -1 : ans;
    }
};
