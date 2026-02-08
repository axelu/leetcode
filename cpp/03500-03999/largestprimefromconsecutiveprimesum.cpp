
// 3770. Largest Prime from Consecutive Prime Sum
// https://leetcode.com/problems/largest-prime-from-consecutive-prime-sum/



// initialize once
vector<int> primesumprimes;
bool init = false;


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

public:
    int largestPrime(int n) {
        // 1 <= n <= 5 * 1e5

        if( !init ) {
            int sum = 0;
            for(int i = 2; i <= 500000; ++i) {
                if( isPrime(i) ) {
                    sum = sum + i;
                    if( sum > 500000 )
                        break;
                    if( isPrime(sum) )
                        primesumprimes.push_back(sum);
                }
            }
            init = true;
        }

        if( n == 1 )
            return 0;

        auto lb = lower_bound(begin(primesumprimes), end(primesumprimes), n);
        if( lb == primesumprimes.end() )
            return primesumprimes.back();
        else if( *lb == n )
            return n;
        else
            return *(prev(lb));
    }
};
