
// 2761. Prime Pairs With Target Sum
// https://leetcode.com/problems/prime-pairs-with-target-sum/



class Solution {
private:
    // prime number generator optimized Sieve of Eratosthenes
    // source https://www.geeksforgeeks.org/program-to-print-first-n-prime-numbers/
    vector<int> primeGenerator(int n) {
        // 2 < n
        // returns array of primes up to and including n

        bool prime[n/2];
        memset(prime,false,sizeof(prime));

        for(int i = 3; i*i < n; i += 2) {
            if( prime[i/2] == false )
                for(int j = i*i; j < n; j += i*2)
                    prime[j/2] = true;
        }

        vector<int> ret{2};

        for(int i = 3; i < n; i += 2)
            if( prime[i/2] == false)
                ret.push_back(i);

        return ret;
    }

public:
    vector<vector<int>> findPrimePairs(int n) {
        // 1 <= n <= 10e6
        if( n < 4 )
            return {};

        // worst case:
        // there are 78,498 primes in range[2,1000000] inclusive
        // 2, ..., 999983
        vector<int> primes = primeGenerator(n);

        vector<vector<int>> ans;

        for(auto it = primes.begin(); it != primes.end(); ++it) {
            int t = n - *it;
            if( binary_search(it,primes.end(),t) )
                ans.push_back({*it,t});
        }

        return ans;
    }
};
