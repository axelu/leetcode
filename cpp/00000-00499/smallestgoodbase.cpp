

// 483. Smallest Good Base
// https://leetcode.com/problems/smallest-good-base/ 







class Solution {
private:
    string convertToBase(long x, long base) {
        string r = "";
        while( x > 0 ) {
            long long t = x % base;
            r = to_string(x % base) + r;
            x /= base;
        }
        return r;
    }

    long solve(unsigned long long base, int i, unsigned long long target) {
        // target provided for an early exit

        unsigned long long ret = 0;
        unsigned long long mul = 1;
        for(int k = 0; k < i; ++k) {
            ret += mul;
            if( ret > target )
                return LONG_MAX;
            if( k < i-1 && mul > target/base ) // overflow
                return LONG_MAX;
            mul *= base;
            //if( k < i-1 && mul > target )
            //    return LONG_MAX;
        }
        return ret;
    }

    // binary search
    long search(long s, long e, long target, int i) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        long mid = s + ((e-s)/2);
        // cout << "mid " << mid << endl;

        long t = solve(mid,i,target);
        // cout << "t " << t << endl;
        if( t == target )
            return mid;
        else if( t > target )
            return search(s,mid-1,target,i);
        else
            return search(mid+1,e,target,i);
    }

public:
    string smallestGoodBase(string n) {
        // n is an integer in the range [3, 10^18]
        // the goal is to minimize the base

        // best case  => base 2
        // worst case => base n-1
        // worst case base n-1 is always a solution

        // n = base^i + ... + base^3 + base^1 + base^0
        // as we are asked to minimize the base,
        // we are looking for the 'longest possible', meaning the largest i
        // 1000000000000000000 10^18
        // 9223372036854775807 base 2 63bits
        // 4611686018427387903 base 2 62bits
        // 2305843009213693951 base 2 61bits
        // 1152921504606846975 base 2 60bits
        //  576460752303423487 base 2 59bits

        long x = stol(n);
        long s = 2;
        long e = x-1;

        for(int i = 60; i >= 2; --i) {
            long base = search(s,e,x,i);
            if( base != -1 )
                return to_string(base);
        }

        return to_string(x-1);
    }
};
