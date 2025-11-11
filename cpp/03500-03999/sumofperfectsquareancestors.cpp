
// 3715. Sum of Perfect Square Ancestors
// https://leetcode.com/problems/sum-of-perfect-square-ancestors/

// idea for speedup: lazily precompute the odd prime factors for each
//                   value in range 1..100000


// initialize once
bool perfect_squares[100001];
bool init = false;

class Solution {
private:
    // prime factorization
    vector<int> primeFactors(long long n) {
        // returns sorted list of prime factors of n that occur an odd number of times

        map<int,int> mp;
        // the number of 2s that divide n
        while(n % 2LL == 0LL) {
            // cout << 2 << " ";
            ++mp[2];
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(long long i = 3; i <= sqrt(n); i = i + 2LL) {
            while(n % i == 0LL) {
                // cout << i << " ";
                ++mp[i];
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2LL ) {
            // cout << n << " ";
            ++mp[n];
        }

        // go through our map and collect the prime factors
        // the occur and odd number of times in ascending order
        vector<int> v;
        for(auto p: mp)
            if( p.second % 2 )
                v.push_back(p.first);

        return v;
    }

    long long ans;

    void rec(vector<int> g[], vector<int>& nums, int u, int src, int& a, map<vector<int>,int>& mp, bool seen[]) {
        seen[u] = true;

        // a = number of perfect squares in current path
        // mp key: vector of odd prime factors, value: count

        bool isperfectsquare = perfect_squares[nums[u]];
        vector<int> oddpfs;
        if( isperfectsquare ) {
            ans += (long long)a;
            ++a;
        } else {
            oddpfs = primeFactors(nums[u]);
            auto f = mp.find(oddpfs);
            if( f != mp.end() )
                ans += (long long)f->second;
            ++mp[oddpfs];
        }

        // recurse
        for(int v: g[u])
            if( v != src )
                rec(g, nums, v, u, a, mp, seen);

        // backtrack
        if( isperfectsquare ) {
            --a;
        } else {
            --mp[oddpfs];
            if( mp[oddpfs] == 0 )
                mp.erase(oddpfs);
        }

        return;
    }

public:
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
        // 1 <= n <= 1e5
        // 1 <= nums[i] <= 1e5
        // mn_pf 2 mx_pf 99991

        if( !init ) {
            memset(perfect_squares,false,sizeof perfect_squares);
            for(long i = 1; i*i <= 100000; ++i)
                perfect_squares[i*i] = true;
            init = true;
        }

        // - if two numbers are a perfect square,
        //   their product is a perfect square
        //   example 4 * 16 = 64
        // - a perfect square has an even number of prime factors and
        //   each primefactor occurs an even number of times

        vector<int> g[100000]; // undirected tree rooted in 0
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        ans = 0LL;

        int a = 0;
        map<vector<int>,int> mp;
        bool seen[100000];memset(seen,false,sizeof seen);
        rec(g, nums, 0, -1, a, mp, seen);

        return ans;
    }
};
