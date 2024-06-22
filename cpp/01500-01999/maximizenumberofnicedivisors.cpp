
// 1808. Maximize Number of Nice Divisors
// https://leetcode.com/problems/maximize-number-of-nice-divisors/






class Solution {
private:
    // prime factorization
    vector<int> primeFactors(int n) {
        // returns list of distinct prime factors
        unordered_set<int> us;
        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            us.insert(2);
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                us.insert(i);
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            us.insert(n);
        }

        vector<int> ret(us.begin(),us.end());
        reverse(ret.begin(),ret.end());
        return ret;
    }

    vector<int> get_divisors(int n) {
        vector<int> ret;
        ret.push_back(1);
        int i_limit = n/2;
        for(int i = 2; i <= i_limit; ++i)
            if( n % i == 0 )
                ret.push_back(i);

        ret.push_back(n);
        return ret;
    }

    long mod = 1000000007;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }

public:
    int maxNiceDivisors(int primeFactors) {
        if( primeFactors == 1 )
            return 1;

        /*
        int n = 200; // 108
        cout << "n = " << n << endl;
        auto distinct_primes = this->primeFactors(n);
        cout << " distinct prime factors: ";
        for(int dpf: distinct_primes)
            cout << dpf << " ";
        cout << endl;
        auto divisors = get_divisors(n);
        cout << " divisors: ";
        for(int divisor: divisors)
            cout << divisor << " ";
        cout << endl;
        cout << " nice divisors: ";
        int nd = 0;
        for(int divisor: divisors) {
            bool f = true;
            for(int dpf: distinct_primes) {
                if( divisor % dpf ) {
                    f = false;
                    break;
                }
            }
            if( f ) {
                cout << divisor << " ";
                ++nd;
            }
        }
        cout << endl;
        cout << " number of nice divisors: " << nd << endl;
        */

        // we need to maximize the number of 'nice' divisors
        // oberservation / hint 1: number of nice divisors is equal to the product of the count of each prime factor.
        // so we get the maximum product if we divide into blocks of 3 and/or 2 of the same prime factor
        // examples
        //   10 -> 3 3 3 1 : 3 + 3 + 3 + 1 = 10; 3 * 3 * 3 * 1 = 27
        //      -> 3 3 2 2 : 3 + 3 + 2 + 2 = 10; 3 * 3 * 2 * 2 = 36  <= max = ans
        //   11 -> 3 3 3 2 : 3 + 3 + 3 + 2 = 11; 3 * 3 * 3 * 2 = 54

        int k = primeFactors / 3;
        int rem = primeFactors % 3;
        if( rem == 0 ) {
            return modular_pow(3,k);
        } else if( rem == 1 ) {
            return (modular_pow(3,k-1) * 4) % mod;
        } else {
            return (modular_pow(3,k) * 2) % mod;
        }

    }
};
