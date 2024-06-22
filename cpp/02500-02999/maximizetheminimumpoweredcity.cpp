
// 2528. Maximize the Minimum Powered City
// https://leetcode.com/problems/maximize-the-minimum-powered-city/




class Solution {
private:
    long long power[100000];
    long long line[100001];
    int n, r, k;

    bool solve(long long target) {
        bool ret = true;

        // lets build a new line
        long long rem = k;
        memset(line,0LL,sizeof line);
        long long prev = 0;
        for(int i = 0; i < n; ++i) {
            // number of stations feeding the current city
            long long current = prev + power[i] + line[i];
            long long build = 0;
            if( current < target ) {
                // we need to build (target - current) stations
                // we will build the plant farthest to the right (greedy) at min(n-1,i+r)
                // we have rem remaining stations
                build = target - current;
                rem -= build;
                if( rem < 0LL ) {
                    ret = false;
                    break;
                }
            }
            int right = min(n-1,i+(2*r));
            line[right + 1] = -build;
            prev += build + line[i];
        }
        // cout << "solve target " << target << " return " << ret << endl;
        return ret;
    }

    // binary search
    long long search(long long s, long long e) {
        if( s > e )
            return -1LL;

        long long mid = s + ((e-s)/2LL);
        bool f = solve(mid);
        if( f ) {
            // can we do better?
            long long t = search(mid+1LL,e);
            return t != -1LL ? t : mid;
        }

        return search(s,mid-1LL);
    }

public:
    long long maxPower(vector<int>& stations, int r, int k) {
        n = stations.size();
        this->r = r;
        this->k = k;

        // lets get the number of power stations feeding each city
        memset(line,0LL,sizeof line);
        for(int i = 0; i < n; ++i) {
            // the stations of the current city provide
            // power to all cities in range [left,right] inclusive
            int left = max(0,i-r);
            int right = min(n-1,i+r);
            line[left] += (long long)stations[i];
            line[right+1] -= (long long)stations[i];
        }
        long long prev = 0LL;
        long long mx = 0LL;
        long long mn = LLONG_MAX;
        for(int i = 0; i < n; ++i) {
            power[i] = prev + line[i];
            mx = max(mx, power[i]);
            mn = min(mn, power[i]);
            prev = power[i];
        }
        // cout << "mn " << mn << " mx " << mx << endl;

        if( k == 0 ) // edge case
            return mn;

        return search(mn,mx+k);
    }
};
