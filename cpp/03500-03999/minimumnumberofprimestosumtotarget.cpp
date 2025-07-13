
// 3610. Minimum Number of Primes to Sum to Target
// https://leetcode.com/problems/minimum-number-of-primes-to-sum-to-target/


// initialize once
bool init = false;
int primes[1000];

class Solution {
private:
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

    // binary search
    int search(int n, int target) {
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( primes[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && primes[s] > target) || s == n )
            --s;

        return s;
    }

    const int INF = 1000;
    int mem[168][1001];

    int rec(int pos, int n) {
        if( n == 0 )
            return 0;

        if( n < 1 || pos < 0 )
            return INF;

        if( mem[pos][n] != -1 )
            return mem[pos][n];

        int ret = INF;

        // how many times does primes[pos] fit into n?
        int f = n / primes[pos];
        for(int i = f; i >= 0; --i) {
            int n_new = n - (i * primes[pos]);
            ret = min(ret, i + rec(pos-1, n_new));
        }

        return mem[pos][n] = ret;
    }


public:
    int minNumberOfPrimes(int n, int m) {
        if( !init ) {
            init = true;
            for(int i = 2, cnt = 0; cnt < 1000; ++i) {
                if( isPrime(i) ) {
                    primes[cnt++] = i;
                }
            }
        }

        // cout << primes[999] << endl; // 7919

        if( n == 1 )
            return -1;

        // find the largest prime number <= n
        int t = search(m, n); // index in primes
        // if m = 1000 and n = 1000, then t = 167, primes[167] = 997

        memset(mem,-1,sizeof mem);
        int ans = rec(t, n);
        return ans < 1000 ? ans : -1;
    }
};
