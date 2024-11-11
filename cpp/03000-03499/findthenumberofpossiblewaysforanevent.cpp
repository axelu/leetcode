
// 3317. Find the Number of Possible Ways for an Event
// https://leetcode.com/problems/find-the-number-of-possible-ways-for-an-event/



// https://www.mathsisfun.com/combinatorics/combinations-permutations.html
// https://brilliant.org/wiki/distinct-objects-into-identical-bins/  includes distinct objects into identical bins, including: distinct objects into identical non empty bins
// Stirling number https://www.geeksforgeeks.org/calculate-stirling-numbers-which-represents-the-number-of-ways-to-arrange-r-objects-around-n-different-circles/
// just for reference also https://brilliant.org/wiki/distinct-objects-into-distinct-bins/
// https://math.stackexchange.com/questions/2756239/distributing-distinct-objects-into-distinct-bins-if-each-bin-can-hold-one-object

/* example n = 3, x = 3, y = 4 --> ans = 684
 *     abc||
 *     ab|c|
 *     a|bc|
 *     |abc|
 *     ab||c
 *     a|b|c
 *     a||bc
 *     |ab|c
 *     |a|bc
 *     ||abc
 *     ... 27 different distributions total x^n
 *     per problem statement, even ab|c| and ab||c are considered different
 *
 *  so we know that each non-empty stage will give us y^(number of non-empty stages),
 *  as we can rate each non-empty stage from 1..y
 *  let our performers be a,b and c
 *  1 non-empty stage
 *      y^(number of non-empty stages) = 4^1 = 4
 *      a) distribute 3 distinct objects (our 3 performers) into 1 identical non-empty bins (1 non-empty stages)
 *          result 1
 *      b) distribute 1 distinct objects (our different partitions of performers aka non-empty stages) into 3 distinct objects (our stages) hoding at most 1
 *          P(n,k) (n stages, k partitions) P(3,1) = 3
 *      ==> 4 * 1 * 3 = 12
 *  2 non-empty stages
 *      y^(number of non-empty stages) = 4^2 = 16
 *      a) distribute 3 distinct objects (our 3 performers) into 2 identical non-empty bins (2 non-empty stages)
 *          result 3
 *      b) distribute 2 distinct objects (our different partitions of performers aka non-empty stages) into 3 distinct objects (our stages) hoding at most 1
 *          P(n,k) (n stages, k partitions) P(3,2) = 6
 *      ==> 16 * 3 * 6 = 288
 *  3 non-empty stages
 *      y^(number of non-empty stages) = 4^3 = 64
 *      a) distribute 3 distinct objects (our 3 performers) into 3 identical non-empty bins (3 non-empty stages)
 *          result 1
 *      b) distribute 3 distinct objects (our different partitions of performers aka non-empty stages) into 3 distinct objects (our stages) hoding at most 1
 *          P(n,k) (n stages, k partitions) P(3,3) = 6
 *      ==> 64 * 1 * 6 = 384
 *  putting it all together:  12 + 288 + 384 = 684
 *
 * example n = 2, x = 2, y = 2  --> ans = 12
 *     dist    rate the non-empty stage(s):  count
 *     ab|     1    2                            2
 *     a|b     1,1  1,2  2,1  2,2                4
 *     |ab     1    2                            2
 *     b|a     1,1  1,2  2,1  2,2                4
 *                                           ======
 *                                              12
 */


// initialize once
long  factorial[1001];
bool init = false;
long memS[1001][1001];



class Solution {
private:
    const long mod = 1000000007;

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

    long modInverse(long a) {
        // return modular multiplicative of: a mod MOD
        return modular_pow(a,mod-2);
    }

    long modPermutations(long n, long k) {
        // regular permutations formula P(n,k) = n!/(n-k)!
        // return P(n,k) mod MOD
        /*
        long numerator = 1; // n!
        int i;
        for(i=1;i<=n;i++) numerator = (numerator*i) %mod;

        long denominator = 1; // n-k!
        for(i=1;i<=n-k;i++) denominator = (denominator*i) %mod;
        */
        long numerator = factorial[n];
        long denominator = factorial[n-k];

        long res = modInverse(denominator);
        res = (res*numerator)%mod;
        return res;
    }

    long modCombinations(long n, long k) {
        // regular combinations formula C(n,k) = n!/(k!(n-k)!)
        // return C(n,k) mod MOD
        long numerator = 1; // n*(n-1)* ... * (n-k+1)
        int i;
        for(i=0;i<k;i++) numerator = (numerator*(n-i))%mod;

        /*
        long denominator = 1; // k!
        for(i=1;i<=k;i++) denominator = (denominator*i) %mod;
        */
        long denominator = factorial[k];

        long res = modInverse(denominator);
        res = (res*numerator)%mod;
        return res;
    }

    long stirlingNumber(long n, long r) {
        // cout << "stirlingNumber n " << n << " r " << r << endl;
        /*
        General Case of Stirling Nubers of the SECOND KIND (!!! different than just Stirling Numbers)
        https://brilliant.org/wiki/distinct-objects-into-identical-bins/
        Let there be n distinct objects to be distributed among r identical bins.
        r > n    ⟹ S(n,r) = 0.
        r = n    ⟹ S(n,n)   = 1r = n ⟹ S(n,n)=1.
        r = n−1  ⟹ S(n,n−1) = (n2)r=n−1⟹S(n,n−1)=(2n​).
        r = n−2  ⟹ S(n,n−2) = (n3)+3(n4)r=n−2⟹S(n,n−2)=(3n​)+3(4n​).
        r = 1    ⟹ S(n,1)   = 1r=1⟹S(n,1)=1.
        r = 2    ⟹ S(n,2)   = 2n−1−1.r=2⟹S(n,2)=2n−1−1.
        */

        if( memS[n][r] != -1 )
            return memS[n][r];

        long ret;

        if (r > n)
            ret = 0;

        else if (r == n)
            ret = 1;

        else if (r == n-1)
            ret = modCombinations(n, 2);

        else if (r == n-2)
           ret = (modCombinations(n, 3) + ((3 * modCombinations(n, 4)) % mod)) % mod;

        else if ( r == 1 )
            ret = 1;

        else if (r == 2)
            ret =  modular_pow(2, n-1) - 1L;

        else
            ret = (((r * stirlingNumber(n - 1, r)) % mod) + stirlingNumber(n - 1, r - 1)) % mod;

        return memS[n][r] = ret;
    }

public:
    int numberOfWays(int n, int x, int y) {

        if( !init ) {
            init = true;

            // pre-calculate modular factorial
            factorial[0] = 1L;
            factorial[1] = 1L;
            for(long i = 2; i <= 1000; ++i)
                factorial[i] = (factorial[i-1] * i) % mod;

            // TODO precompute the inverse of the factorials

            memset(memS,-1,sizeof memS);
            stirlingNumber(1000,1000);
        }



        // there are n distinct objects (our performers)
        // that are to be distributed among r distinct bins (in our case to x stages).
        // This can be done in precisely r^n ways, in our case x^n ways.

        // now in each of those distributions, we can assign any non-empty stages
        // any possible comination of scores between 1..y
        // more precisely: to all non-empty stages (order matters) we can apply y ratings with repetition
        // --> permutation with repetition
        //         ratings           ratings     x     ratings     ...
        //          1..y              1..y              1..y
        //     ---------------   ---------------   ---------------
        //     non-empty stage   non-empty stage   non-empty stage
        //     y^(number of non-empty stages in a given distribution)
        //

        // edge cases
        if( y == 1 ) // 1 possible rating
            return modular_pow(x, n);
        if( x == 1 ) // 1 stage
            return y;
        if( n == 1 ) // 1 performer
            return x * y;


        long ans = 0L;

        long y_factor = (long)y;

        for(int non_empty_stages = 1; non_empty_stages <= min(n,x); ++non_empty_stages) {

            // number ways we can distribute of n distinct performers onto identical non_empty_stages
            // S(n,non_empty_stages);
            long f1 = stirlingNumber(n, non_empty_stages);

            // number ways we can distribute the distinct non_empty_stages across all our stages x if each stage can hold one non-empty stage
            // P(x, non_empty_stages)
            long f2 = modPermutations(x, non_empty_stages);

            // y_factor * f1 * f2
            long t = (((y_factor * f1) % mod) * f2) % mod;

            // cout << "non_empty_stages " << non_empty_stages << " y_factor " << y_factor << " f1 " << f1 << " f2 " << f2 << " t " << t << endl;

            ans = (ans + t) % mod;

            y_factor = (y_factor * y) % mod;
        }

        return ans;
    }
};
