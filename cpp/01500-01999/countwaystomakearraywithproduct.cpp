
// 1735. Count Ways to Make Array With Product
// https://leetcode.com/problems/count-ways-to-make-array-with-product/



/*
 * example k = 660
 * 660 can be represented by the following prime factors not including 1
 * prime factorization
 * 660 = 2 * 2 * 3 * 5 * 11
 * now lets assume we have 10 positions (0-indexed) to distribute
 * any possible partition of these prime factors to
 * example of one such partition
 *   0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9
 *  2*2 |     |  3  |     |  5  |  11 |     |     |     |
 * Note: in the position we have empty, we will put a 1
 * so we need to figure out the number of possible paritions
 * the interesting part here is that we have two 2s
 * so we need to figure out how many ways we can distribute identical
 * factors into n positions
 * this is known as the 'stars and bars' problem
 * https://cp-algorithms.com/combinatorics/stars_and_bars.html
 */

class Solution {
private:
    long mod = 1000000007;

    // the most number of prime factors any number between
    // 1 and 10000 has is 13
    void a() {
        int mx = 0;

        for(int i = 1; i <= 10000; ++i) {
            cout << i << " ";
            int t = 0;
            int k = i;
			// prime factorization of k
			for(int j = 2; j * j <= k; ++j)
				if (k % j == 0) {
					while( k % j == 0 ) {
						k /= j;
                        ++t;
                    }
				}
			if( k > 1 )
				++t;
            cout << t << endl;
            mx = max(mx,t);
        }
        cout << mx << endl;
    }

    // ... and hence our dp limits are:
    int mem[10014][14];

    // binomial coefficient
    // number of ways to select a set of k elements from n different
    // elements without taking into account the order of arrangement
    // of these elements
    // https://cp-algorithms.com/combinatorics/binomial-coefficients.html
    int C(int n, int k) {
        if( k == 0 || k == n )
            return 1;

        if( mem[n][k] != -1 )
            return mem[n][k];

        return mem[n][k] = (C(n-1,k-1) + C(n-1,k)) % mod;
    }

public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        int q_sz = queries.size();

        vector<int> ans(q_sz);

        memset(mem,-1,sizeof mem);

        for(int i = 0; i < q_sz; ++i) {
            int n = queries[i][0]; // 1 <= n <= 10000
            int x = queries[i][1]; // 1 <= x <= 10000

            // prime factorization of x
            // get the prime factors we can divide x into
            long t = 1;
            for(int j = 2; j <= x; ++j)
				if( x % j == 0 ) {
                    int k = 0; // nbr identical primes
					while (x % j == 0) {
						x /= j;
                        // cout << j << endl; // j is a prime factor
                        ++k;
                    }
                    t = (t * C(k + n - 1,k)) % mod;
                }
            ans[i] = t;
        }

        return ans;
    }
};
