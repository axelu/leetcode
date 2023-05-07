
// 2507. Smallest Value After Replacing With Sum of Prime Factors
// https://leetcode.com/problems/smallest-value-after-replacing-with-sum-of-prime-factors/





class Solution {
private:
    // prime factorization
    int primeFactors(int n) {
        // returns sum of prime factors
        int sum = 0;

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            sum += 2;
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                sum += i;
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            sum += n;
        }

        return sum;
    }

public:
    int smallestValue(int n) {

        int tt1 = INT_MAX;
        int ans = primeFactors(n);
        while( ans < tt1 ) {
            tt1 = ans;
            ans = primeFactors(ans);
        }

        return ans;
    }
};
