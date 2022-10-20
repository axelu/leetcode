
// 2187. Minimum Time to Complete Trips
// https://leetcode.com/problems/minimum-time-to-complete-trips/





class Solution {
private:
    bool solve(vector<int>& time, long t, long totalTrips) {
        long trips = 0;
        for(auto& x: time) {
            trips += t / x;
            if( trips >= totalTrips )
                return true;
        }
        return false;
    }

    // binary search
    long search(long s, long e, vector<int>& time, int totalTrips) {
        if( s > e )
            return -1;

        long mid = s + ((e-s)/2);
        bool f = solve(time,mid,totalTrips);
        if( f ) {
            // can we do better?
            long t = search(s,mid-1,time,totalTrips);
            return t != -1 ? t : mid;
        }
        return search(mid+1,e,time,totalTrips);
    }


public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        // from the constraints:
        //     1 <= time[i], totalTrips <= 10^7
        // hence worst case:
        //     we have one bus that takes 10^7 time to complete one trip
        //     and we have to complete 10^7 total trips
        //     answer: 10^7 x 10^7

        return search(0,100000000000000,time,totalTrips);
    }
};
