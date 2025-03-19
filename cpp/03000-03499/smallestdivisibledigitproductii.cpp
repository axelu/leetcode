
// 3348. Smallest Divisible Digit Product II
// https://leetcode.com/problems/smallest-divisible-digit-product-ii/







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

    string create(long long divisor, int len) {
        // cout << "create divisor " << divisor << " len " << len << endl;
        // returns the smallest zero free string
        // that is at least length long and
        // whos digit product is divisble by divisor

        string ret = "";
        for(long long i = 9; i > 1; --i) {
            while( divisor % i == 0 ) {
                ret.push_back(i+'0');
                divisor /= i;
            }
        }
        reverse(ret.begin(),ret.end());
        if( ret.size() < len ) {
            int t = len - ret.size();
            string prefix(t, '1'); // fill with 1's to the left
            ret = prefix + ret;
        }

        return ret;
    }


public:
    string smallestNumber(string num, long long t) {
        int n = num.size();

        // we can figure out if there is a solution first
        // if we factor t into its prime factors (primefactorization) and
        // t has a prime factor greater 7, there is no solution
        // primes below 10: 2, 3, 5, 7

        vector<int> _primefactors = primeFactors(t); // sorted primefactor list
        if( _primefactors.back() > 7 )
            return "-1";

        // if num is divisible by t, then num is the answer
        int left_most_zero = -1;
        vector<long long> divisible(n+1, t);
        for(int i = 1; i <= n; ++i) {
            if( num[i-1] == '0' ) {
                left_most_zero = i-1;
                break;
            }
            long long x = num[i-1] - '0';
            divisible[i] = divisible[i-1] / gcd(divisible[i-1], x);
        }
        /*
        for(long long i: divisible)
            cout << i << " ";
        cout << endl;
        */
        if( divisible[n] == 1LL )
            return num;

        // we could create the smallest possible number
        // out of the prime factors, if it is equal or greater num we are done

        // we cannot have any zeros, so if our num has 0s, the left most zero is
        // our starting point, otherwise we start at n-1
        // we move from right to left in num
        // the idea is to find the shortest zero free 'suffix' from starting point
        // that would make our num greater and is divisible by t
        for(int i = left_most_zero != -1 ? left_most_zero : n-1; i >= 0; --i) {
            int len = (n-1) - i; // remaining length to our right
            long long div = divisible[i];
            // we will try by increasing the digit at the current position
            for(int j = (num[i]-'0') + 1; j < 10; ++j) {
                // we need to adjust what num to our left is divisble by
                long long div_new = div / gcd(div, (long long)j);

                // cout << "trying at i " << i << " original num[i] " << num[i] << " the following " << j << endl;
                string suffix = create(div_new, len);

                if( suffix.size() == len ) {
                    string prefix = num.substr(0,i);
                    prefix.push_back(j+'0');
                    return prefix + suffix;
                }
            }
        }

        // if we are still here, we need to create a longer string
        return create(t, n+1);
    }
};
