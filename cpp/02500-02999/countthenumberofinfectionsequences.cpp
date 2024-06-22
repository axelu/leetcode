
// 2954. Count the Number of Infection Sequences
// https://leetcode.com/problems/count-the-number-of-infection-sequences/





/*
 * observation
 *     if a range of lenght m of non-infected children is surrounded on both ends by an infected child,
 *     then there are 2 ^ (m-1) ways to get all children in that range infected, because it can happen
 *     from both ends
 *     example INNNNI  -> m = 4 -> 2 ^ (m-1) = 2 ^ (4-1) - 2 ^ 3 = 8 (I = infected, N = non-infected)
 *             I1234I
 *             I1342I
 *             I1432I
 *             I1243I
 *             I4321I
 *             I2431I
 *             I2341I
 *             I3421I
 *     so every infection sequence of a range of non-infected children that is surrounded on both ends by an infected child
 *     can be combined, so we need to multiply the number of ways with each other
 *     for the beginning and end, there could be a range that is not surrounded on both ends, those can only get completely
 *     infected in one way: NNNNNI...
 *                          54321I...
 *
 *     now additionally, the seqences of non-infected children in a given range can interweave with other ranges,
 *     which makes it a stars and bars combination problem,
 *     lets assume three ranges, range 1 has A non-infected children, range 2 has B non-infected children, range 3 has C non-infected children,
 *     the children in each range are indistinguishable, what is the number of combinations to arrange them in a row?
 *     AAAAABBBBCCCCCCC
 *     -> (A + B + C)! / A! * B! *C!
 */
class Solution {
private:
    const long mod = 1000000007;

    // TODO move to global and detect if initialized once
    long factorial[100001];

    void fact(long n) {
        for(long i = 2; i <= n; ++i)
            factorial[i] = (factorial[i-1] * i) % mod;
        return;
    }

    long long modPow(long long a, long long x) {
        // return a^x % mod
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a % mod
        return modPow(a,mod-2);
    }

    // modular division
    long modDivide(long a, long b) {
        // a = a % mod;
        long inv = modInverse(b);
        return (inv * a) % mod;
    }

public:
    int numberOfSequence(int n, vector<int>& sick) {
        // 2 <= n <= 1e5

        // precompute factorials
        factorial[1] = 1L;
        fact(n);
        // TODO we could also precompute the inverse of the factorials

        long nbr_infected_children = sick.size();
        long nbr_noninfected_children = n - nbr_infected_children;

        long ans = factorial[nbr_noninfected_children];

        // is there a range on non-infected children at the very beginning?
        if( sick[0] != 0 ) {
            int m = sick[0];
            // ans = modDivide(ans,factorial[m]);            // interweave
            ans = (ans * modInverse(factorial[m])) % mod; // interweave
        }

        // process ranges on non-infected children that have an infected child on both ends
        for(int i = 1; i < sick.size(); ++i){
            int m = sick[i] - sick[i-1] - 1;
            if( m == 0 )
                continue;
            // ans = modDivide(ans,factorial[m]);            // interweave
            ans = (ans * modInverse(factorial[m])) % mod; // interweave
            ans = (ans * modPow(2,m-1)) % mod;            // combine
        }

        // is there a range on non-infected children at the very end?
        if( sick[sick.size()-1] != n-1 ) {
            int m = n - sick[sick.size()-1] - 1;
            // ans = modDivide(ans,factorial[m]);            // interweave
            ans = (ans * modInverse(factorial[m])) % mod; // interweave
        }

        return ans;
    }
};
