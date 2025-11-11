
// 3733. Minimum Time to Complete All Deliveries
// https://leetcode.com/problems/minimum-time-to-complete-all-deliveries/





class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // function to return Least Common Multiple (LCM) of two numbers
    // LCM definition:
    // LCM of two numbers is the smallest number which can be divided by both numbers
    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }

    long long minTime(long long d, long long r) {
        // in one interval, we make r - 1 deliveries
        // r - 1    d
        // ----- = ---
        //   r0     a
        // a is the hour in which the drone is doing its last delivery
        long long a = (r * d) / (r - 1LL);
        if( (r * d) % (r - 1LL) == 0LL )
            --a;

        return a;
    }

    long long minTime(long long d0, long long d1, long long r0, long long r1, long long _lcm) {
        // a is the hour in which drone 0 is doing its last delivery
        long long a = minTime(d0, r0);
        // how many times did we recharge?
        long long acharges = a / r0;

        // cout << "a " << a << " acharges " << acharges << endl;

        // drone 1
        // drone 1 makes a delivery every time drone 0 recharges
        // unless drone 0 recharge hour was also a drone 1 recharge hour
        long long ocharges = a / _lcm; // overlapping recharge hours
        // cout << " ocharges " << ocharges << endl;

        // drone 1 remaining deliveries
        d1 = d1 - (acharges - ocharges);
        if( d1 <= 0LL )
            return a;

        // drone 1 starts making its remaining deliveries at a + 1
        // when is drone 1's next recharge hour after hour a?
        long long next_charge1 = (((long long)(a / r1)) * r1) + r1;
        // cout << "next_charge1 " << next_charge1 << endl;
        // drone 1 will make deliveries in the hours a+1 ... next_charge1-1
        long long d1_before_next_charge = next_charge1 - (a+1LL);
        if( d1_before_next_charge >= d1 )
            return a + d1;

        // drone 1 remaining deliveries
        d1 = d1 - d1_before_next_charge;

        // drone 1 will make remaining deliveries start next_charge1 + 1
        long long b = minTime(d1, r1);

        return next_charge1 + b;
    }

    bool solve(long long d0, long long d1, long long r0, long long r1, long long _lcm, long long t) {
        // cout << "solve t " << t << endl;

        // how many charging hours for drone 0 within t?
        long long charges0 = t / r0; // cout << "  charges0 " << charges0 << endl;
        // how many charging hours for drone 0 within t?
        long long charges1 = t / r1; // cout << "  charges1 " << charges1 << endl;
        // how many charging hours overlap?
        long long ocharges = t / _lcm; // cout << "  ocharges " << ocharges << endl;

        // hours in which only drone 0 can deliver
        long long t0 = charges1 - ocharges; // cout << "  t0 " << t0 << endl;
        // hours in which only drone 1 can deliver
        long long t1 = charges0 - ocharges; // cout << "  t1 " << t1 << endl;

        // remaining deliveries of drone 0 after it optimally uses hours when drone 1 is charging
        d0 = max(0LL, d0-t0);
        // remaining deliveries of drone 1 after it optimally uses hours when drone 0 is charging
        d1 = max(0LL, d1-t1);

        // hours in which drone 0 or drone 1 can deliver
        t = t - ((charges0 + charges1) - ocharges);

        return t >= d0 + d1;
    }

    // binary search
    long long search(long long d0, long long d1, long long r0, long long r1, long long _lcm,
                     long long s, long long e) {

        if( s > e )
            return -1LL;

        long long mid = s + ((e-s)/2LL);
        bool f = solve(d0, d1, r0, r1, _lcm, mid);
        if( f ) {
            // can we do better?
            long long t = search(d0, d1, r0 , r1, _lcm, s, mid-1LL);
            return t != -1LL ? t : mid;
        }

        return search(d0, d1, r0 , r1, _lcm, mid+1LL, e);
    }

public:
    long long minimumTime(vector<int>& d, vector<int>& r) {
        // worst case d0 == d1 == 1e9 and r0 == r1 == 2

        // if r[0] == r[1], then it is sequential
        // we can treat it as one drone making _d = d[0] + d[1] deliveries
        if( r[0] == r[1] ) {
            // let _r = r[0] = r[1]
            // in one interval, we make _r - 1 deliveries
            // _r-1   _d
            // ---- = ---
            //  _r     a
            // a is the hour in which we are doing the last delivery
            long long _d = (long long)(d[0] + d[1]);
            long long _r = (long long)r[0];
            long long a = (_r * _d) / (_r-1LL);
            if( (_r * _d) % (_r-1LL) == 0LL )
                --a;

            return a;
        }

        long long _lcm = lcm(r[0], r[1]);

        // we have one drone do its deliveries
        // every time it recharges, we have the other drone do a delivery
        // if and only if its recharge hour does not overlap
        long long m01 = minTime(d[0], d[1], r[0], r[1], _lcm);
        long long m10 = minTime(d[1], d[0], r[1], r[0], _lcm);

        // we maybe be able to do better than that
        // example
        // d = [9,7], r = [3,4] => ans 17
        // c charge, * delivery
        //     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
        // d0  c  *  *  c  *  *  c  *  *  c  *  *  c        c  *
        // d1  c        *  c     *     c  *        c  *  *  *  c  *

        // binary search
        // max is the smaller of m01 and m10
        // min is the larger of what it would take for one drone alone
        //     to do its delivery by itself
        long long a = minTime(d[0], r[0]);
        long long b = minTime(d[1], r[1]);

        return search(d[0], d[1], r[0], r[1], _lcm, max(a,b), min(m01,m10));

    }
};
