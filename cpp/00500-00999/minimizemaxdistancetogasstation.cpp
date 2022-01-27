
// 774. Minimize Max Distance to Gas Station
// https://leetcode.com/problems/minimize-max-distance-to-gas-station/
// day 15 September 2021 challenge bonus question
// https://leetcode.com/explore/featured/card/september-leetcoding-challenge-2021/638/week-3-september-15th-september-21st/3975/





class Solution {
private:

    bool possible(double D, vector<double>& distances, int n, int k) {
        // cout << "possible D " << D << endl;
        double d;
        int t;
        for(int i = 0; i < n; ++i) {
            // number of stations to add between station[i] and station[i-1]
            // in order to get to a distance <= D
            if( distances[i] <= D )
                t = 0;
            else
                t = ceil(distances[i]/D)-1;

            k -= t;
            if( k < 0 )
                return false;
        }

        return true;
    }

    // binary search
    double search(vector<double>& distances, int n, int k, double s, double e) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1.0;

        double mid = s + ((e-s)/2.0);
        if( possible(mid,distances,n,k) ) {
            // can we do better?
            double t = search(distances,n,k,s,mid-0.000001);
            return t == -1.0 ? mid : t;
        } else {
            return search(distances,n,k,mid+0.000001,e);
        }
    }

public:
    double minmaxGasDist(vector<int>& stations, int k) {
        int n = stations.size(); // 10 <= stations.length <= 2000
        // constraints given:
        //      0 <= stations[i] <= 10^8
        //      stations is sorted in a strictly increasing order.
        // that means there are no duplicates
        //      1 <= k <= 10^6

        // example:
        // stations = {1,2,3,4,5,6,7,8,9,10};
        // k        = 1000000;
        // ans     -> 0.00001

        // our solutions space is [0.0,max dist between two adjacent stations]

        vector<double> distances(n-1);
        double d;
        double mx = 0.0;
        for(int i = 0; i < n-1; ++i) {
            d = stations[i+1] - stations[i];
            distances[i] = d;
            mx = max(mx,d);
        }

        double ans = search(distances,n-1,k,0.0,mx);
        return ans == -1.0 ? mx : ans;
    }
};
