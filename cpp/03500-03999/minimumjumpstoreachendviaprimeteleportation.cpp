
// 3629. Minimum Jumps to Reach End via Prime Teleportation
// https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/





// initialize once
int is_prime[1000001]; // lazy population
bool init = false;

class Solution {
private:
    bool isPrime(int n) {
        if( is_prime[n] != -1 )
            return is_prime[n];

        if( n == 2 || n == 3 )
            return is_prime[n] = true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return is_prime[n] = false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return is_prime[n] = false;
        }

        return is_prime[n] = true;
    }

public:
    int minJumps(vector<int>& nums) {
        if( !init ) {
            init = true;
            memset(is_prime,-1,sizeof is_prime);
        }

        int n = nums.size(); // 1 <= n <= 1e5; 1 <= nums[i] <= 1e6
        // there are 78,498 primes between 2-1e6 inclusive

        // inventory the prime numbers in nums
        // for each prime number in nums, inventory the indexes j,
        //     where nums[j] % p == 0
        //     respectively nums[j] is a multiple of the given prime

        // pass 1
        map<int, vector<int>> int2idx;  // key: integer value: indices i where nums[i] = key
        int mx = -1;                    // max value of nums[i]
        for(int i = 0; i < n; ++i) {
            int2idx[nums[i]].push_back(i);
            mx = max(mx, nums[i]);
        }

        // Dijkstra
        // min heap -> array<int,2> {steps, vertex}
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[100000];
        for(int i = 0; i < n; ++i)
            A[i] = INT_MAX;

        // push our source vertex into priority queue
        int s = 0;
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        set<int> seen;
        map<int, vector<int>> multiples; // key: p value: list of indices i where nums[i] % p == 0

        int u,v;
        while(!pq.empty()) {

            u = pq.top()[1]; // index
            if( u == n-1 )
                return pq.top()[0];
            pq.pop();

            // we can jump to 'adjacent'
            v = u-1;
            if( v >= 0 && A[v] > A[u] + 1 ) {
                // Updating distance of v
                A[v] = A[u] + 1;
                pq.push({A[v], v});
            }
            v = u+1;
            if( v < n && A[v] > A[u] + 1 ) {
                // Updating distance of v
                A[v] = A[u] + 1;
                pq.push({A[v], v});
            }

            int p = nums[u];
            if( isPrime(p) ) {
                // we are at u
                // we can jump to any index v where nums[v] % p == 0, except u

                // if we have already seen p, then
                // we already know the indices v where nums[v] % p == 0,
                // otherwise we need to determine those
                if( seen.insert(p).second ) {
                    int f = 1;
                    while( p * f <= mx ) {
                        auto it = int2idx.find(p*f);
                        if( it != int2idx.end() ) {
                            for(int i : it->second) {
                                multiples[p].push_back(i);
                            }
                        }
                        ++f;
                    }

                    for(auto it = multiples[p].begin(); it != multiples[p].end(); ++it) {
                        v = *it;
                        if( v == u )
                            continue;

                        //  If there is shorter path to v through u.
                        if( A[v] > A[u] + 1 ) {
                            // Updating distance of v
                            A[v] = A[u] + 1;
                            pq.push({A[v], v});
                        }
                    }
                }
            }
        }

        return A[n-1];
    }
};
