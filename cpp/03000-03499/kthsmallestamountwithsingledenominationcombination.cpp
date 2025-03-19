
// 3116. Kth Smallest Amount With Single Denomination Combination
// https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/





class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    // Returns factorial of n
    long long fact(int n) {
        long long res = 1;
        for (int i = 2; i <= n; i++)
            res = res * (long long)i;
        return res;
    }

    long long nCr(int n, int r) {
        return fact(n) / (fact(r) * fact(n - r));
    }

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

    long long solve(vector<int>& coins, long long amount) {
        // coins is sorted
        // with one of the denominations

        int n = coins.size();
        int c = pow(2,n)-1;     // combinations of coins that make same value
        vector<long long> cnt(n+1,0LL);
        for(int i = 1; i <= c; ++i) {
            int _setbits = countSetBits(i);
            long long _lcm = -1;
            for(int j = 0; j < n; ++j) {
                if( i & (1<<j) ) {
                    if( _lcm == -1 )
                        _lcm = coins[j];
                    else
                        _lcm = lcm(_lcm, coins[j]);
                }
            }
            // how many times does our _lcm fit into amount?
            long long t = amount / _lcm;
            cnt[_setbits] += t;
        }
        // debug
        /*
        for(int i = 1; i <= n; ++i)
            cout << i << ":" << cnt[i] << " ";
        cout << endl;
        */

        // we need to reduce our counts by the overlaps
        for(int i = n; i > 1; --i) {

            for(int j = i-1; j > 1; --j) {
                cnt[j] -= nCr(i,j) * cnt[i];
            }

            cnt[1] -= (i-1) * cnt[i];
        }

        return cnt[1];
    }

    // binary search
    long long search(vector<int>& coins, long long s, long long e, long long k) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1LL;

        long long mid = s + ((e-s)/2LL);
        // long long mid_alt = next_smaller(coins, mid);

        // what number amount is this?
        long long x = solve(coins, mid);
        // cout << "solve for " << mid << " res " << x << endl;

        if( x >= k ) {
            // can we do better?
            long long t = search(coins, s, mid-1, k);
            return t != -1LL ? t : mid;
        }

        return search(coins, mid+1, e, k);
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        // 1 <= coins[i] << 25; 1 <= k <= 2000000000
        // 25LL * 2000000000LL = 50000000000
        // INT_MAX                2147483647

        int n = coins.size();
        if( n == 1 )
            return (long long)coins[0] * (long long)k;

        sort(begin(coins),end(coins));

        if( k == 1 )
            return (long long)coins[0];
        if( coins[0] == 1 )
            return (long long)k;

        /*
        denominations will 'interweave' and 'overlap'
        example [3,6,9]
        3   3 6 9 12 15 18 21 24 27
        6     6   12    18    24
        9       9       18       27
        in this case only the 3 matters -> ans = 3 * k

        example [5,2]
        2   2 4 6 8 10 12 14 16 18 20
        5      5    10      15     20
        so for k = 7 -> ans = 12
               k = 9 -> ans = 15
         */

        // simplify
        // if we have a multiple in coin denomination, we can delete it
        vector<int> del(n,0);
        for(int i = 0; i < n; ++i) {
            if( del[i] )
                continue;
            for(int j = i+1; j < n; ++j) {
                if( coins[j] % coins[i] == 0 )
                    del[j] = 1;
            }
        }
        /*
        for(int i: coins)
            cout << i << " ";
        cout << endl;
        for(int i: del)
            cout << i << " ";
        cout << endl;
        */
        int del_idx = 0;
        for(auto it = coins.begin(); it != coins.end(); ) {
            if( del[del_idx] )
                it = coins.erase(it);
            else
                ++it;
            ++del_idx;
        }
        /*
        for(int i: coins)
            cout << i << " ";
        cout << endl;
        */
        n = coins.size();
        if( n == 1 )
            return (long long)coins[0] * (long long)k;

        // our answer is between something >= coins[0] and coins[n-1] * k
        long long e = (long long)coins[n-1] * (long long)k;
        return search(coins, coins[0], e, k);
    }
};
