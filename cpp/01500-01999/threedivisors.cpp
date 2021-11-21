
// 1952. Three Divisors
// https://leetcode.com/problems/three-divisors/
// https://leetcode.com/contest/weekly-contest-252/problems/three-divisors/





class Solution {
private:
    /*
    bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }
    */

    public:
    bool isThree(int n) {
        // an integer m is a divisor of n
        // if there exists an integer k such that n = k * m

        // 1 is always a divisor of n
        // n itself is a divisor of n

        if( n <= 3 )
            return false;

        // if n is a prime, the answer is false
        // if n is prime*prime, the answer is yes

        // primes less than 100
        int primes[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
        for(int i = 0; i < 25; ++i)
            if( primes[i]*primes[i] == n )
                return true;

        return false;
    }
};
