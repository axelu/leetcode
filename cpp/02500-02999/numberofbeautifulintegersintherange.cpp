
// 2827. Number of Beautiful Integers in the Range
// https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/





class Solution {
private:
    pair<int,int> count_digits(int x) {
        int odd = 0;
        int even = 0;
        while( x ) {
            int rem = x % 10;
            if( rem % 2 )
                ++odd;
            else
                ++even;
            x /= 10;
        }
        return {odd, even};
    }

    int k;
    vector<int> lo_v;
    vector<int> hi_v;

    vector<int> int2vector(int num) {
        vector<int> ret;
        while( num > 0 ) {
            ret.push_back(num % 10);
            num /= 10;
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }

    int mem[9][2][9][9][2][2][20];

    int rec(int lft, int start, int odd, int even, int le, int te, int rem) {
        // lft   = number of remaining positions example 87654321, 1 is last position
        //                                               10000000
        // start = is start, then we cannot use 0
        // odd   = number of odd digits used so far
        // even  = number of odd digits used so far
        // le    = is low edge?
        // te    = is top edge?
        // rem   = rem

        if( lft == 0 )
            return odd == even && rem == 0 ? 1 : 0;

        if( mem[lft][start][odd][even][le][te][rem] != -1 )
            return mem[lft][start][odd][even][le][te][rem];

        int ret = 0;

        int i = start ? 1 : 0;

        int lo_v_sz = lo_v.size();
        int lo = lo_v[lo_v_sz - lft];
        int hi_v_sz = hi_v.size();
        int hi = hi_v[hi_v_sz - lft];

        for(; i <= 9; ++i) {
            if( le && i < lo )
                continue;
            if( te && i > hi )
                continue;

            int odd_new = odd;
            int even_new = even;
            if( i % 2 )
                ++odd_new;
            else
                ++even_new;

            int le_new = 0;
            if( le && i == lo )
                le_new = 1;
            int te_new = 0;
            if( te && i == hi )
                te_new = 1;

            int rem_new = (rem * 10 + i) % k;

            ret += rec(lft - 1, 0, odd_new, even_new, le_new, te_new, rem_new);
        }

        return mem[lft][start][odd][even][le][te][rem] = ret;
    }

public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        // 0 < low <= high <= 1e9

        // edge cases
        if( high <= 9 )
            return 0;
        if( low == high ) {
           auto[odd, even] = count_digits(low);
           return odd == even && low % k == 0 ? 1 : 0;
        }

        // if number digits low is odd, then low is next higher 10^x
        // e.g. low = 356 -> low = 1000
        // if number digits high is odd, then high is next one down
        // e.g. high = 357 -> high = 99
        // e.g. high = 14357 -> high = 9999

        auto[lo_odd, lo_even] = count_digits(low);
        if( (lo_odd + lo_even) % 2 ) {
            low = pow(10, lo_odd + lo_even);
        }

        auto[hi_odd, hi_even] = count_digits(high);
        if( (hi_odd + hi_even) % 2 ) {
            high = pow(10, hi_odd + hi_even - 1) - 1;
        }

        // max high 1000000000
        // there is no way to make a number with with equal even and odd digits in range [100000000,1000000000]
        if( high > 99999999 )
            high = 99999999;

        // cout << "low  " << low << endl;
        // cout << "high " << high << endl;

        if( low > high )
            return 0;
        if( low == high ) {
           auto[odd, even] = count_digits(low);
           return odd == even && low % k == 0 ? 1 : 0;
        }

        /*

        // we need to pay special attention to the following
        // let low = 1000, high = 9999, k = 1
        // so 1001 meets our criteria
        // if not first two digits
        // 00 0 odd 2 even
        // 01 1 odd 1 even
        // 02 0 odd 2 even
        // 03 1 odd 1 even
        // 04 0 odd 2 even
        // 05 1 odd 1 even
        // 06 0 odd 2 even
        // 07 1 odd 2 even
        // 08 0 odd 2 even
        // 09 1 odd 1 even

        // lets find all numbers in the range of [10,99] inclusive divisible by k
        // lets split them into three types
        // type 0 1 odd and 1 even digit
        // type 1 2 odds
        // type 2 2 evens

        int type0 = 0, type1 = 0, type2 = 0;
        for(int i = 10; i <= 99; ++i) {
            if( i % k )
                continue;
            auto[odd,even] = count_digits(i);
            if( odd == 1 )
                ++type0;
            else if( odd == 2 )
                ++type1;
            else
                ++type2;
        }
        int zeroninetype0 = 0, zeroninetype1 = 0, zeroninetype2 = 0;
        for(int i = 0; i <= 9; ++i) {
            if( i % k )
                continue;
            auto[odd,even] = count_digits(i);
            if( odd == 1 )
                ++zeroninetype0;
            else
                ++zeroninetype2;
        }

        int t = type0 * type0;
        t += type0 * zeroninetype0;
        t += (type1 * type2) * 2;
        t += type1 * zeroninetype2;

        cout << "t " << t << endl;

        int cnt = 0;
        for(int i = 1000; i <= 9999; ++i) {
            if( i % k )
                continue;
            auto[odd,even] = count_digits(i);
            if( odd == even ) {
                ++cnt;
                cout << i << endl;
            }
        }

        cout << "cnt " << cnt << endl;
        */

        // only these ranges
        // 10000000 99999999    8
        //   100000 999999      6
        //     1000 9999        4
        //       10 99          2

        vector<int> lo_v_org = int2vector(low);
        lo_v = int2vector(low);
        hi_v = int2vector(high);
        this->k = k;

        while( lo_v.size() < hi_v.size() )
            lo_v.insert(lo_v.begin(),0);

        memset(mem,-1,sizeof mem);
        int ans = 0;
        for(int l = lo_v_org.size(); l <= hi_v.size(); l += 2) {
            int le = l == lo_v_org.size() ? 1 : 0;
            int te = l == hi_v.size() ? 1 : 0;
            // cout << "l " << l << " le " << le << " te " << te << endl;
            ans += rec(l, 1, 0, 0, le, te, 0);
        }

        return ans;
    }
};
