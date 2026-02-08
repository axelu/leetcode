
// 3790. Smallest All-Ones Multiple
// https://leetcode.com/problems/smallest-all-ones-multiple/


class Solution {
private:
    // prime factorization
    vector<int> primeFactors(long long n) {
        // returns list of prime factors
        // v is ordered from smallest to largest
        vector<int> v;
        // the number of 2s that divide n
        while(n % 2LL == 0LL) {
            // cout << 2 << " ";
            v.push_back(2);
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(long long i = 3; i <= sqrt(n); i = i + 2LL) {
            while(n % i == 0LL) {
                // cout << i << " ";
                v.push_back(i);
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2LL ) {
            // cout << n << " ";
            v.push_back(n);
        }

        return v;
    }

    bool divByK(int n, int k) {
        // checks if a number with n 1's is divisible by k
        int rem = 0; // running remainder
        for(int i = n-1; i >= 0; --i) {
            rem = (rem * 10 + 1) % k;
        }
        return rem == 0;
    }

public:
    int minAllOneMultiple(int k) {
        // 2 <= k <= 1e5
        // if k is even, there is no solution
        if( k % 2 == 0 )
            return -1;

        // examples
        // k = 99999 -> ans = 45
        // k = 99997 -> ans = 7866
        // k = 99995 -> ans = -1
        // k = 99993 -> ans = 33330

        // brute force
        /*
        int kdigits = to_string(k).size();
        for(int i = kdigits; i <= 33330; ++i) // i_max given range of k ???
            if( divByK(i, k) )
                return i;
        */

        /*
        // no pattern seen for 1, 11, 111, 1111, ...
        string n = "";
        for(int i = 0; i < 20; ++i) {
            n.push_back('1');
            auto v = primeFactors(stoull(n));
            cout << n << endl;
            for(int pf: v)
                cout << pf << " ";
            cout << endl;
        }
        */

        /*
        int rem = 0; // running remainder
        for(int i = 1; i <= 33330; ++i) { // how far do we go ???
            rem = (rem * 10 + 1) % k;
            if( rem == 0 )
                return i;
        }
        return -1;
        */

        // if we see the remainder again, we are going in circles
        // hence we can abort
        bool seen[100001]; memset(seen, false, sizeof seen);
        int rem = 0;
        seen[0] = true;
        int i = 1;
        for(; ; ++i) {
            rem = (rem * 10 + 1) % k;
            if( seen[rem] )
                break;
            seen[rem] = true;
        }

        return rem == 0 ? i : -1;
    }
};
