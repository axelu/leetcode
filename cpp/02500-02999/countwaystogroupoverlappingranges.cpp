
// 2580. Count Ways to Group Overlapping Ranges
// https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/




class Solution {
private:
    // returns the number of intervals after merging
    int merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if( n == 1 )
            return 1;

        sort(begin(intervals),end(intervals));

        int _back = intervals[0][1];
        int cnt = 1;

        for(int j = 1; j < n; ++j) {
            if( intervals[j][0] > _back ) {
                _back = intervals[j][1];
                ++cnt;
            } else if( intervals[j][0] == _back ) {
                _back = intervals[j][1];
            } else if( intervals[j][1] > _back ) {
                _back = intervals[j][1];
            }
        }

        return cnt;
    }

    long MOD = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % MOD;
            a = (a*a) % MOD;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,MOD-2);
    }

    long long numerator;
    long long denominator;

    long long modCombinations(long long n, long long k) {
        // regular combinations formula C(n,k) = n!/(k!(n-k)!)
        // return C(n,k) mod MOD
        /*
        long long numerator = 1; // n*(n-1)* ... * (n-k+1)
        int i;
        for(i=0;i<k;i++) numerator = (numerator*(n-i))%MOD;

        long long denominator = 1; // k!
        for(i=1;i<=k;i++) denominator = (denominator*i) %MOD;
        */
        long long res = modInverse(denominator);
        res = (res*numerator)%MOD;
        return res;
    }


public:
    int countWays(vector<vector<int>>& ranges) {

        int n = merge(ranges);

        // we need to distribute range_cnt intervals to two groups
        // we can put 0 intervals into group A and range_cnt intervals in group  B
        // we can put range_cnt intervals in group A and  0 intervals into group B
        // -> that gives at least 2 ways
        // we can next put range_cnt-1 in group A and 1 in group B
        // we cycle through that as which item we put in group B matters
        //    respectively it matters which items are left in group A
        // do the same with range_cnt-2 in group A and 2 in group B
        // and so on

        long ans = 2;

        numerator = n;
        denominator = 1;

        for(int k = 1; k < n; ++k) {

            denominator = (denominator*k) %MOD;

            long long t = modCombinations(n,k);
            ans = (ans + t) %MOD;

            numerator = (numerator*(n-k))%MOD;
        }

        return ans;
    }
};
