
// 2188. Minimum Time to Finish the Race
// https://leetcode.com/problems/minimum-time-to-finish-the-race/


/* extreme example
 * tires [[100000,100000]], changeTime = 100000, numLaps = 1000
 * => answer  199900000
 */

class Solution {
private:
    int n;
    int _numLaps;
    int _changeTime;
    vector<vector<int>> tt; // tire, laptime

    int mem[1000];

    int rec(const int lap) {
        // cout << "rec lap " << lap << " tire " << tire << endl;
        if( lap == _numLaps )
            return -_changeTime;

        if( mem[lap] != -1 )
            return mem[lap];

        // at the end of each lap we have a choice
        //    continue with the current tire OR
        //    put on a new tire (including the tire we had)

        int ret = 1000000000;

        for(int tire = 0; tire < tt.size(); ++tire) {
            int t = 0;

            for(int lap_cnt = 0; lap_cnt < tt[tire].size() && lap+lap_cnt+1 <= _numLaps; ++lap_cnt) {

                // continue with current tire
                t = t + tt[tire][lap_cnt];
                if( t > ret )
                    break;
                ret = min(ret, t + _changeTime + rec(lap+lap_cnt+1));
            }
        }

        return mem[lap] = ret;
    }

public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        // tires[i] = [fi, ri] indicates that the ith tire
        // can finish its xth successive lap in fi * ri^(x-1) seconds

        n = tires.size();

        // precompute the times to go around the track on
        // a given tire between 1 and numLaps rounds
        // What is the maximum number of times we would want to go around the track without changing tires?
        // rephrased: What is the maximum number of times we would want to go around w/ current tires?
        //    if the xth lap (x > 0) takes longer than changeTime + f

        sort(tires.begin(),tires.end());
        for(int tire = 0; tire < n; ++tire) { // tire
            // eliminate duplicates
            if( tire > 0 && tires[tire-1][0] == tires[tire][0] && tires[tire-1][1] == tires[tire][1] )
               continue;

            tt.push_back({tires[tire][0]});
            long r = 1, t;
            for(int lap = 1; lap < numLaps; ++lap) {

                // fi * ri^(x-1)

                r = tires[tire][1] * r;
                t = tires[tire][0] * r;
                if( t >= changeTime + tt.back()[0] )
                    break;
                tt.back().push_back(t);
            }
        }

        /*
        // debug
        for(int tire = 0; tire < tt.size(); ++tire) {
            for(int lap = 0; lap < tt[tire].size(); ++lap)
                cout << tt[tire][lap] << " ";
            cout << endl;
        }
        */

        _changeTime = changeTime;
        _numLaps = numLaps;

        memset(mem,-1,sizeof mem);
        return rec(0);
    }
};
