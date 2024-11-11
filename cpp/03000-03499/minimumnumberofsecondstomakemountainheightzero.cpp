
// 3296. Minimum Number of Seconds to Make Mountain Height Zero
// https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/





class Solution {
private:

    // binary search
    int search1(int s, int e, long long mx_seconds, long long workerTime) {
        // returns the max height a worker contributes when she works up to mx_seconds
        if( s > e )
            return -1;

        long long mid = s + ((e-s)/2);
        // to shop of height mid by this worker takes sec seconds
        long long sec = workerTime * (mid * (mid+1)/2LL);
        if( sec == mx_seconds ) {
            return mid;
        } else if( sec < mx_seconds ) {
            // can we do better?
            int t = search1(mid+1, e, mx_seconds, workerTime);
            return t != -1 ? t : mid;
        } else {
            return search1(s, mid-1, mx_seconds, workerTime);
        }
    }

    bool solve(vector<int>& workerTimes, long long mx_seconds, int target) {
        int n = workerTimes.size();

        // we let each worker i work for seconds and add what the will chop of till we reach target

        int total = 0;
        for(int i = 0; i < n; ++i) {

            long long height = 0;
            long long s = 0;

            while( s + workerTimes[i] * (height + 1) <= mx_seconds ) {
                s = s + workerTimes[i] * (height + 1);
                ++height;
            }

            total = total + height;
            if( total >= target )
                return true;
        }

        return false;
    }

    // binary search
    long long search(vector<int>& workerTimes, long long s, long long e, int target) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1LL;

        long long mid = s + ((e-s)/2LL);
        auto f = solve(workerTimes, mid, target);
        if( f ) {
            // can we do better?
            long long t = search(workerTimes, s, mid-1LL, target);
            return t != -1LL ? t : mid;
        }

        return search(workerTimes, mid+1LL, e, target);
    }

public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {

        // to decrease the mountain's height by x,
        //     it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x seconds
        // worst case
        //     mountainHeight = 100000
        //     1 worker {1000000}
        //     1000000 + 1000000 * 2 + ... + 1000000 * 100000
        //     -> workerTime * (sum from 1 to x) -> workerTime * (x * (x+1)/2)
        //
        //     5000050000000000 seconds

        /*
        long long a = 1LL;
        for(int i = 2; i <= 100000; ++i)
            a = a + (long long)i;
        cout << a << endl;
        cout << LLONG_MAX << endl;
        long long b = (long long)100000 * (100000+1)/2;
        cout << b << endl;
        cout << b * 1000000LL << endl;
        */

        // slowest worker == highest worker time
        sort(workerTimes.begin(),workerTimes.end());
        // time it would take the slowest worker by herself reduce the height
        int worker_sz = workerTimes.size();
        long long mx = (long long)workerTimes[worker_sz - 1] * ( (long long)mountainHeight * (mountainHeight+1)/2LL );

        return search(workerTimes, 1LL, mx, mountainHeight);
    }
};
