
// 3449. Maximize the Minimum Game Score
// https://leetcode.com/problems/maximize-the-minimum-game-score/






class Solution {
private:
    bool solve(vector<int>& points, long long m, long long target) {
        int n = points.size(); // 3 <= n

        // special handling of i = n-2
        int nminus2visits;

        int carry = 0;
        for(int i = 0; i < n; ++i) {
            if( i == n-2 ) {
                // we made 1 move to get here
                // we already have been carry times here
                // do we have enough moves?
                m = m - (carry + 1);
                if( m < 0 )
                    return false;
                nminus2visits = carry + 1;
                carry = 0;
                continue;
            }

            // we need to elevate points[i] to at least target
            // by visiting points[i] a certain number of times
            long long f = target / (long long)points[i];
            if( target % (long long)points[i] )
                ++f;
            // we need to visit points[i] f times
            // we made 1 move to get here
            // we already have been carry times here

            if( carry + 1 >= f ) {
                // do we have enough moves?
                m = m - (carry + 1);
                if( m < 0 )
                    return false;
                carry = 0;

            } else {
                long long rem = f - (carry + 1);
                // do we have enough moves?
                m = m - (rem + carry + 1);
                if( m < 0 )
                    return false;
                carry = rem;
            }
        }
        // finish up
        // we are sitting on position n-1
        // we need to check position n-2
        // we visited points[n-2] nminus2visits + carry times
        // we already accounted for the nminus2visits
        // did we have enough moves for the carry visits
        m = m - carry;
        if( m < 0 )
            return false;
        // how many more times do we need to vist n-2?
        long long nminus2f = target / (long long)points[n-2];
        if( target % (long long)points[n-2] )
            ++nminus2f;
        if( nminus2visits + carry < nminus2f ) {
            long long rem = nminus2f - (nminus2visits + carry);
            // we are at n-1, and then we jump back and forth
            long long rem_total = rem + (rem-1);
            if( rem_total > m )
                return false;
        }

        return true;
    }

    // binary search
    long long search(vector<int>& points, int m, long long s, long long e) {
        if( s > e )
            return -1LL;

        long long mid = s + ((e-s)/2LL);
        if( solve(points, m, mid) ) {
            // can we do better?
            long long t = search(points, (long long)m, mid+1, e);
            return t != -1LL ? t : mid;
        }

        return search(points, m, s, mid-1);
    }


public:
    long long maxScore(vector<int>& points, int m) {
        // 1 <= m <= 1e9
        int n = points.size(); // 2 <= n <= 50000; 1 <= points[i] <= 1e6

        // gameScore array of size n
        // initially gameScore[i] = 0 for all 0 <= i < n
        // first move is always to index 0, and gameScore[0] becomes points[0]
        if( m == 1 || m < n ) {
            // if m == 1
            //     n is at least 2, we cannot make another move,
            //     so gameScore[i] for 1 <= i < n will be 0
            // if m < n
            //     we can only jump up to i = m-1
            //     so gameScore[i] for m <= i < n will be 0
            return 0LL;
        }
        if( n == m ) {
            // we jump to each position once
            return (long long)*min_element(begin(points),end(points));
        }
        if( n == 2 ) {
            // we jump back and forth as often as we can
            // index 0  1
            //       1  2
            //       3  4
            //       5  6
            //       ...
            long long f0 = m / 2;
            if( m % 2 )
                ++f0;
            long long f1 = m / 2;
            long long v0 = (long long)points[0] * f0;
            long long v1 = (long long)points[1] * f1;
            return min(v0, v1);
        }

        // let us assume that to increase a value most efficiently,
        // we hope between it at i and i+1 back and forth
        // except the value at n-1, we must hope back and forth i, i-1
        // we can set a goal and see given m if we make it or run out of moves
        // via binary search
        // our max for binary search would be min(points) * m, min 0

        // example points = [3,2,5,2,7,4], m = 50 => ans 20
        // bool tt1 = solve(points, 50, 21);
        // cout << tt1 << endl;
        // example points = [5,2,6], m = 13 => ans 18
        // bool tt1 = solve(points, 13, 18);
        // cout << tt1 << endl;


        return search(points, m, 0LL, 1000000000000000LL);
    }
};




/* test cases

[2,4]
3
[1,2,3]
5
[1000000,1000000]
1000000000
[1000000,1000000]
999999999
[3,2,5,2,7,4]
50
[5,3,6]
13


*/
